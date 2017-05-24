#!/usr/bin/env python
# coding=utf-8
"""
排序算法 : {"选择排序":select_sort, "快速排序":quick_sort, "归并排序": merge_sort}
E-mail: yuxiao2113@gmail.com
"""

import random
import time


def adjust_lst(lst, begin, end):
    i = begin
    j = end
    tmp = lst[begin]

    while j > i:
        while j > i and lst[j] >= tmp:
            j -= 1
        if j > i and lst[j] < tmp:
            lst[i] = lst[j]

        while j > i and lst[i] < tmp:
            i += 1
        if j > i and lst[i] >= tmp:
            lst[j] = lst[i]

    assert i == j
    lst[i] = tmp

    return i


def quick_sort(lst, begin, end):
    if end <= begin:
        return

    sentinel = adjust_lst(lst, begin, end)
    quick_sort(lst, begin, sentinel-1)
    quick_sort(lst, sentinel + 1, end)


def swap(lst, i, j):
    tmp = lst[i]
    lst[i] = lst[j]
    lst[j] = tmp


def select_sort(lst):
    assert lst != []
    lstlen = len(lst)

    for i in range(lstlen):
        minv_index = i
        for j in range(i + 1, lstlen):
            if lst[j] < lst[minv_index]:
                minv_index = j
        swap(lst, i, minv_index)


def merge(lst, left, mid, right):
    llst = lst[left:mid + 1]
    rlst = lst[mid + 1:right + 1]

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

    assert k == right + 1


def merge_sort(lst, begin, end):
    assert lst != [] and end >= begin

    if begin >= end:
        return

    mid = (end - begin) / 2 + begin
    merge_sort(lst, begin, mid)
    merge_sort(lst, mid + 1, end)
    merge(lst, begin, mid, end)


def elapse(f):
    def wrapper(*args, **kw):
        start = time.time()
        f(*args, **kw)
        end = time.time()
        print f.__name__, "=> elapse %f secs" % (end - start)
        print ""

    return wrapper


@elapse
def test_sort_algorithm():
    maxvalue = 10000000
    minvalue = -10000000
    lstlen = 100
    cnt = 1000
    for i in range(cnt):
        lsti = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        lstj = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        lstk = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        assert len(lsti) == lstlen
        assert len(lstj) == lstlen
        assert len(lstk) == lstlen

        print "before sort"
        print lsti
        print lstj
        print lstk

        sorted_lst = sorted(lstj)
        merge_sort(lstj, 0, lstlen - 1)
        assert sorted_lst == lstj

        sorted_lst = sorted(lsti)
        select_sort(lsti)
        assert sorted_lst == lsti

        sorted_lst = sorted(lstk)
        quick_sort(lstk, 0, lstlen-1)
        assert sorted_lst == lstk

        print "after sort"
        print lsti
        print lstj
        print lstk
        print ""

    print "each list LENGTH is %d, it's OKKKKK to sort each list %d times" % (lstlen, cnt)


@elapse
def test_sort_algorithm_performance():
    maxvalue = 10000000
    minvalue = -10000000
    lstlen = 10000
    cnt = 10
    for i in range(cnt):
        lsti = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        lstj = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        lstk = [random.randint(minvalue, maxvalue) for j in range(lstlen)]
        assert len(lsti) == lstlen
        assert len(lstj) == lstlen
        assert len(lstk) == lstlen

        print "=>each list LENGTH is %d" % lstlen

        start = time.time()
        merge_sort(lstj, 0, lstlen - 1)
        end = time.time()
        print "=>elapsed mergesort: %f secs" % (end - start)

        start = time.time()
        quick_sort(lstk, 0, lstlen-1)
        end = time.time()
        print "=> elapsed quicksort: %f secs" % (end - start)

        start = time.time()
        select_sort(lsti)
        end = time.time()
        print "=> elapsed selectsort: %f secs" % (end - start)

        print ""


if __name__ == "__main__":
    test_sort_algorithm()
    test_sort_algorithm_performance()
