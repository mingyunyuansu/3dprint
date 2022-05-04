

#include "InputFromSTL.h"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

//为一个model填充数据
void InputFromSTL::init(OptimizedModel &model) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cout << "open file failed, path: " << path << std::endl;
        exit(-1);
    }
    std::cout << "open " << path << " ok" << std::endl;
    std::string line, tmp;
    std::getline(ifs, line); // file name
    int cnt = 0;
    while (std::getline(ifs, line)) {
//        facet normal -0.060604 0.997443 -0.037878
//        outer loop
//        vertex -0.00110000 0.13140000 0.01460000
//        vertex -0.00160000 0.13110000 0.00750000
//        vertex -0.00410000 0.13110000 0.01150000
//        endloop
//        endfacet
        //if (cnt >= 100) exit(-1);
        std::istringstream iss0;
        iss0.str(line);
        iss0 >> tmp;
        // 遇到文件结尾
        if (tmp == ENDSOLID) {
            break;
        }
        // 先一次性获取三角面的三个点
        std::getline(ifs, line); // 除去法向量行
        std::getline(ifs, line);
        std::istringstream iss1;
        iss1.str(line);
        double x, y, z;
        //iss >> std::fixed >> std::setprecision(6) >> tmp >> x >> y >> z;
        iss1 >> tmp >> x >> y >> z;
        Point a(x, y, z);
        //std::cout << line << std::endl;
        //std::cout << x << " " << y << " " << z << std::endl;

        std::getline(ifs, line);
        std::istringstream iss2;
        iss2.str(line);
        iss2 >> tmp >> x >> y >> z;
        Point b(x, y, z);
        //std::cout << line << std::endl;
        //std::cout << x << " " << y << " " << z << std::endl;


        std::getline(ifs, line);
        std::istringstream iss3;
        iss3.str(line);
        iss3 >> tmp >> x >> y >> z;
        Point c(x, y, z);
        //std::cout << line << std::endl;
        //std::cout << x << " " << y << " " << z << std::endl;

        std::getline(ifs, line); // 除去结尾两行
        std::getline(ifs, line);

        //std::cout << a.x << " " << b.x << " " << c.x << std::endl;

        int i1 = model.points.size();
        int ni1 = isDupPoint(model, a, i1);
        int i2 = model.points.size();
        int ni2 = isDupPoint(model, b, i2);
        int i3 = model.points.size(); // 三个点的序号
        int ni3 = isDupPoint(model, c, i3);

        if (ni1 != ni2 && ni1 != ni3 && ni2 != ni3) {
            // 三角形三个点没有重复，该三角形有效
            model.facets.emplace_back(ni1, ni2, ni3);
            //添加三角面下标进三个点
            size_t facetIndex = model.facets.size() - 1;
            model.facets[facetIndex].set_model(&model);
            model.pointInFacet[ni1].push_back(facetIndex);
            model.pointInFacet[ni2].push_back(facetIndex);
            model.pointInFacet[ni3].push_back(facetIndex);
        }
        //cnt += 7;
    }
    std::cout << "finish parsing " << path << std::endl;
    for (int i = 0; i < model.facets.size(); ++i) {
        processAdjFacets(model, i);
    }
    std::cout << "finish adj facets process" << std::endl;
    // debuging, 输出每个三角面的邻接三角面，looks good
    // for (auto each: model.adjFacet) {
    //     std::cout << each.first << " ";
    //     for (auto e: each.second) {
    //         std::cout << e << " ";
    //     }
    //     std::cout << std::endl;
    // }

    //debuging, 输出每个点的所有包含三角面
    // for (auto each: model.pointInFacet) {
    //     std::cout << each.first << " ";
    //     for (auto e: each.second) {
    //         std::cout << e << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

int InputFromSTL::isDupPoint(OptimizedModel &model, Point &point, int idx) {
    // 判断一个点是否已有重复点
    size_t h = model.hasher(point);
    int ret = idx;
    if (model.indexMap.find(h) == model.indexMap.end()) {
        model.indexMap[h].push_back(idx); // 该哈希值下甚至没有点
    } else {
        for (int i = 0; i < model.indexMap[h].size(); ++i) {
            int old_point_idx = model.indexMap[h][i];
            if (distance(model, model.points[old_point_idx], point) <= model.epsilon) {
                // 两个点过近（或者就是同一个点）
                ret = old_point_idx;
                break;
            }
        }
        // 哈希初筛通过，但是还需要比对剩下的所有点，以避免哈希冲突
        for (int j = 0; j < model.points.size() && ret == idx; ++j) {
            if (distance(model, model.points[j], point) <= model.epsilon) {
                ret = j;
                break;
            }
        }
    }
    if (idx == ret) {
        // 该点需要加入，没有冲突
        model.points.push_back(point);
    }
    return ret;
}

int InputFromSTL::distance(OptimizedModel& model,  Point&p1, Point &p2) {
    // 计算两点间的距离
    int dx = round(p1.x * model.ratio) - round(p2.x * model.ratio);
    int dy = round(p1.y * model.ratio) - round(p2.y * model.ratio);
    int dz = round(p1.z * model.ratio) - round(p2.z * model.ratio);
    return round(sqrt(dx * dx + dy * dy + dz * dz));
}

void InputFromSTL::processAdjFacets(OptimizedModel &model, int facetId) {
    int p1 = model.facets[facetId].index[0];
    int p2 = model.facets[facetId].index[1];
    int p3 = model.facets[facetId].index[2];
    for (int i = 0; i < model.facets.size(); ++i) {
        if (facetId == i) continue;
        if (found2PointsInFacets(model, i, p1, p2) ||
            found2PointsInFacets(model, i, p1, p3) ||
            found2PointsInFacets(model, i, p2, p3)) {
            model.adjFacet[facetId].push_back(i);
        }
    }
}

bool InputFromSTL::found2PointsInFacets(OptimizedModel &model, int facetId, int p1, int p2) {
    bool found1{false};
    bool found2{false};
    for (int i = 0; i < 3; ++i) {
        if (model.facets[facetId].index[i] == p1) found1 = true;
    }
    for (int i = 0; i < 3; ++i) {
        if (model.facets[facetId].index[i] == p2) found2 = true;
    }
    return found1 && found2;
}