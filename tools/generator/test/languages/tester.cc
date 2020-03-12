// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (c) 2013 Association Prologin <association@prologin.org>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "cxx/api.hh"

extern "C"
{

    void test();
    void test_alert();

    void api_send_me_42(int n)
    {
        assert(n == 42);
    }

    void api_send_me_42_and_1337(int n1, int n2)
    {
        assert(n1 == 42);
        assert(n2 == 1337);
    }

    void api_send_me_true(bool b)
    {
        assert(b);
    }

    void api_send_me_tau(double b)
    {
        assert(b > 6.2831 && b < 6.2832);
    }

    void api_send_me_13_ints(int arg1, int arg2, int arg3, int arg4, int arg5,
                             int arg6, int arg7, int arg8, int arg9, int arg10,
                             int arg11, int arg12, int arg13)
    {
        assert(arg1 == 1);
        assert(arg2 == 2);
        assert(arg3 == 3);
        assert(arg4 == 4);
        assert(arg5 == 5);
        assert(arg6 == 6);
        assert(arg7 == 7);
        assert(arg8 == 8);
        assert(arg9 == 9);
        assert(arg10 == 10);
        assert(arg11 == 11);
        assert(arg12 == 12);
        assert(arg13 == 13);
    }

    int api_returns_42()
    {
        return 42;
    }

    bool api_returns_true()
    {
        return true;
    }

    double api_returns_tau()
    {
        return 6.2831853;
    }

    test_enum api_returns_val1()
    {
        return VAL1;
    }

    std::vector<int> api_returns_range(int m, int n)
    {
        std::vector<int> v(n - m);
        for (int i = m; i < n; ++i)
            v[i - m] = i;
        return v;
    }

    std::vector<int> api_returns_sorted(std::vector<int> l)
    {
        std::sort(l.begin(), l.end());
        return l;
    }

    std::vector<bool> api_returns_not(std::vector<bool> l)
    {
        for (unsigned i = 0; i < l.size(); ++i)
            l[i] = !l[i];
        return l;
    }

    void api_send_me_simple(simple_struct s)
    {
        assert(s.field_i == 42);
        assert(s.field_bool);
    }

    void api_send_me_42s(struct_with_array s)
    {
        assert(s.field_int == 42);
        assert(s.field_int_arr.size() == 42);
        for (auto i : s.field_int_arr)
            assert(i == 42);
        assert(s.field_str_arr.size() == 42);
        for (auto& s2 : s.field_str_arr)
        {
            assert(s2.field_i == 42);
            assert(s2.field_bool);
        }
    }

    void api_send_me_test_enum(test_enum v1, test_enum v2)
    {
        assert(v1 == VAL1);
        assert(v2 == VAL2);
    }

    std::vector<struct_with_array>
    api_send_me_struct_array(std::vector<struct_with_array> l)
    {
        assert(l.size() == 42);
        for (auto& s : l)
            api_send_me_42s(s);
        return l;
    }
}

extern "C" void api_afficher_test_enum(test_enum v)
{
    assert(v == VAL2);
}

extern "C" void api_afficher_simple_struct(simple_struct) {}
extern "C" void api_afficher_struct_with_array(struct_with_array) {}
extern "C" void api_afficher_struct_with_struct(struct_with_struct) {}

int main(int argc, char* argv[])
{
    int count = 100;
    if (argc > 1)
    {
        if (std::string(argv[1]) == "--test-alert")
        {
            test_alert();
            return 0;
        }
        count = std::strtol(argv[1], nullptr, 0);
    }
    for (int i = 0; i < count; ++i)
        test();
}
