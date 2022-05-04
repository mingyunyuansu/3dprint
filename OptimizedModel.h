
#ifndef NEO_OPTIMIZEDMODEL_H
#define NEO_OPTIMIZEDMODEL_H


#include <map>
#include <vector>

#include "Facet.h"
#include "Point.h"

class OptimizedModel {
public:
    int ratio = 10000; // ȡ��ʱ�ľ���
    int epsilon = 2; // �ж�������ľ����Ƿ����
    std::map<size_t, std::vector<int>> indexMap; // �洢��ͬ��ϣֵ�ĵ��±꣬������ٲ���
    std::map<size_t, std::vector<int>> pointInFacet; //描述一个点被哪些facet包含，均为下标
    std::map<size_t, std::vector<int>> adjFacet; //描述一个三角面的邻接三角面有哪些，均为下标
    std::vector<Point> points; // ���в��ظ��ص㣬˳�����������
    std::vector<Facet> facets; // ������ѡ�������棨�еĻ���Ϊ��϶̫С����push������
    size_t hasher(Point& p);
};


#endif //NEO_OPTIMIZEDMODEL_H
