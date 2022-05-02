
#ifndef NEO_OPTIMIZEDMODEL_H
#define NEO_OPTIMIZEDMODEL_H


#include <map>
#include <vector>

#include "Point.h"
#include "Facet.h"

class OptimizedModel {
public:
    int ratio = 10000; // ȡ��ʱ�ľ���
    int epsilon = 2; // �ж�������ľ����Ƿ����
    std::map<size_t, std::vector<int>> indexMap; // �洢��ͬ��ϣֵ�ĵ��±꣬������ٲ���
    std::vector<Point> points; // ���в��ظ��ص㣬˳�����������
    std::vector<Facet> facets; // ������ѡ�������棨�еĻ���Ϊ��϶̫С����push������
    size_t hasher(Point& p);
};


#endif //NEO_OPTIMIZEDMODEL_H
