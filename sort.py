#!/usr/bin/env python
#coding=utf-8
"""
功能：
    实现了选择排序和归并排序。
    分别为merge_sort()和select_sort两个函数。
    另外简单地测试和对比了两者性能，可以发现当输入数据的size越大，则归并排序性能越好。
    这也符合两者时间复杂度的分析，选择排序是O(n**2),归并排序是O(n*log(n))。

E-mail: yuxiao2113@gmail.com
"""

import random
import time


def elapse(f):
    """
    装饰器，用来打印函数的时间开销。
    """
    def wrapper(*args, **kw):
        start = time.time()
        f(*args, **kw)
        end = time.time()
        print f.__name__,"=> elapse %f secs" % (end-start)
    return wrapper


def swap(lst, i, j):
    tmp = lst[i]
    lst[i] = lst[j]
    lst[j] = tmp

def select_sort(lst):
    assert lst != []
    lstlen = len(lst)

    for i in range(lstlen):
        minv_index = i
        for j in range(i+1, lstlen):
            if lst[j] < lst[minv_index]:
                minv_index = j
        swap(lst, i, minv_index)

def merge(lst, left, mid, right):
    """
    merge the list, assume the left/right list is arranged.
    """
    llst = lst[left:mid+1]
    rlst = lst[mid+1:right+1]

    i = j = 0
    k = left
    llen = len(llst)
    rlen = len(rlst)

    while i < llen and j < rlen:
        if llst[i] < rlst[j]:
            lst[k] = llst[i]
            k += 1
            i += 1
        else:
            lst[k] = rlst[j]
            k += 1
            j += 1

    while i < llen:
        lst[k] = llst[i]
        i += 1
        k += 1

    while j < rlen:
        lst[k] = rlst[j]
        j += 1
        k += 1

    assert k == right+1

def merge_sort(lst, begin, end):
    assert lst != [] and end >= begin

    if begin >= end:
        return

    mid  = (end - begin)/2 + begin
    merge_sort(lst, begin, mid)
    merge_sort(lst, mid+1, end)
    merge(lst, begin, mid, end)

def  test_sort_algorithm():
    lst = []
    maxvalue = 10000000
    minvalue = -10000000
    lstlen =  10
    cnt = 1000
    for i in range(cnt):
        lsti = [random.randint(minvalue, maxvalue) for j in  range(lstlen)]
        lstj = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        assert len(lsti) == lstlen
        assert len(lstj) == lstlen
        print "before sort"
        print lsti
        print lstj

        sorted_list = sorted(lstj)
        merge_sort(lstj, 0, lstlen - 1)
        assert sorted_list == lstj

        sorted_list = sorted(lsti)
        select_sort(lsti)
        assert sorted_list == lsti
        print "after sort"
        print lsti
        print lstj
        print ""


    print "each list LENGTH is %d, it's OKKKKK to sort each list %d times" %  (lstlen, cnt)

@elapse
def test_sort_algorithm_performance():
    from timeit import Timer
    lst = []
    maxvalue = 10000000
    minvalue = -10000000
    lstlen =  100000
    cnt = 2
    for i in range(cnt):
        lsti = [random.randint(minvalue, maxvalue) for j in  range(lstlen)]
        lstj = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        assert len(lsti) == lstlen
        assert len(lstj) == lstlen

        start = time.time()
        merge_sort(lstj, 0, lstlen - 1)
        end = time.time()
        print "=>elapsed mergesort: %f secs" % (end-start)


        start = time.time()
        select_sort(lsti)
        end = time.time()
        print "=> elapsed selectsort: %f secs" % (end-start)

        print ""



if __name__ == "__main__":
    #test_sort_algorithm()
    test_sort_algorithm_performance()
