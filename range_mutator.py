#!/usr/bin/env python
# -*- coding: utf-8 -*-

""" Generate randomly mutated ranges from some seeds """

import random

seed = 11111
largest_layer = 3
largest_mutator = 10
total_ranges = 100
max_array_num = 10
max_filter_num = 100
prelude = f"// This file is generated with seed = {seed}\n" + """
#include <ranges>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <span>
#include <string>
#include <cstddef>
#include <utility>

struct zsentinel {
    auto operator==(char* p) const -> bool {
        return *p == '\\0';
    }
};

struct zstring {
    char* p;
    auto begin() const -> char* { return p; }
    auto end() const -> zsentinel { return {}; }
};

struct czsentinel {
    auto operator==(const char* p) const -> bool {
        return *p == '\\0';
    }
};

struct czstring {
    const char* p;
    auto begin() const -> const char* { return p; }
    auto end() const -> czsentinel { return {}; }
};

template<typename...> struct typelist {};
using random_ranges = typelist<
"""
initials = [
    "bool", "int", "unsigned int", "long", "long long", "char", "signed char", "unsigned char",
    "std::byte", "float", "double", "std::size_t", "std::string", "std::string_view",
    "zstring", "czstring",
    "std::views::iota", "std::views::empty"
]
initial_regular = [x for x in initials if not x.startswith("std::views")]
initial_hash = [x for x in initial_regular if not x.endswith("zstring")]
layers = [
    # standard containers
    "std::array",
    "std::deque",
    "std::forward_list",
    "std::list",
    "std::vector",
    "std::map",
    "std::multimap",
    "std::unordered_map",
    "std::unordered_multimap",
    "std::span"
]
mutators = [
    "ref_remove_all",
    "ref_add_const",
    "ref_add_lref",
    "val_remove_all",
    "val_add_const",
    "decay_to_lower<std::input_iterator_tag>",
    "decay_to_lower_opt<std::forward_iterator_tag>",
    "decay_to_lower_opt<std::bidirectional_iterator_tag>",
    "decay_to_lower_opt<std::random_access_iterator_tag>",
    "to_uncommon", "to_common",
    "to_unsized", "to_sized",
    "to_unconst_iterable", "to_const_iterable",
    "to_unborrowed", "to_borrowed",
    "to_constant",
    "| std::views::all"
]

def apply_initial(initial: str) -> str:
    """ Apply the selected initial """
    if initial == "std::views::iota":
        argnum = random.randint(1, 2)
        args = [random.randint(0, max_filter_num)]
        if argnum == 2:
            args.append(random.randint(args[0], max_filter_num))
        return f"std::remove_cvref_t<decltype({initial}(" + ", ".join(map(str, args)) + "))>"
    if initial == "std::views::empty":
        return f"std::remove_cvref_t<decltype({initial}<{random.choice(initial_regular)}>)>"
    return initial

def apply_layer(current: str, layer: str) -> str:
    """ Apply layer to current """
    if layer == "std::array":
        return f"{layer}<{current}, {random.randint(1, max_array_num)}>"
    if (layer == "std::span" and random.randint(1, 2) == 2):
        return f"{layer}<{current}, 0>"
    if layer.endswith("map"):
        return f"{layer}<{random.choice(initial_hash)}, {current}>"
    return f"{layer}<{current}>"

def apply_mutator(current: str, mutator: str) -> str:
    """ Apply mutator to current """
    if mutator.startswith("|"):
        return f"std::remove_cvref_t<decltype(std::declval<{current}>() {mutator})>"
    return f"std::remove_cvref_t<decltype({mutator}(std::declval<{current}>()))>"

def main() -> None:
    """ Main function """
    random.seed(seed)

    with open("random_ranges.hpp", "w") as fp:
        fp.write(prelude)
        for i in range(total_ranges):
            initial = random.choice(initials)
            apply_layers = random.choices(layers, k=random.randint(0, largest_layer))
            apply_mutators = random.choices(mutators, k=random.randint(0, largest_mutator))
            current = apply_layer(apply_initial(initial), random.choice(layers))
            have_ref = False
            while len(apply_layers) > 0 and len(apply_mutators) > 0:
                ch = random.randint(1, 2)
                if len(apply_layers) == 0 or ch == 2:
                    mutator, apply_mutators = apply_mutators[0], apply_mutators[1:]
                    if mutator.endswith("ref"):
                        if have_ref:
                            continue
                        have_ref = True
                    current = apply_mutator(current, mutator)
                else:
                    layer, apply_layers = apply_layers[0], apply_layers[1:]
                    current = apply_layer(current, layer)
            print(f"[{i + 1:>{len(str(total_ranges))}}/{total_ranges}] {current}")
            fp.write("    " + current + (",\n" if i < total_ranges - 1 else "\n"))
        fp.write(">;\n")

if __name__ == "__main__":
    main()
