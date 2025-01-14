/*
 * Copyright (c) 2020, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/FlyString.h>
#include <AK/Forward.h>
#include <LibGC/Ptr.h>
#include <LibWeb/Forward.h>
#include <LibWeb/HTML/AttributeNames.h>
#include <LibWeb/TreeNode.h>

namespace Web::DOM {

template<typename NodeType>
class NonElementParentNode {
public:
    GC::Ptr<Element> get_element_by_id(FlyString const& id) const
    {
        GC::Ptr<Element> found_element;
        const_cast<NodeType*>(static_cast<NodeType const*>(this))->template for_each_in_inclusive_subtree_of_type<Element>([&](auto& element) {
            if (element.id() == id) {
                found_element = &element;
                return TraversalDecision::Break;
            }
            return TraversalDecision::Continue;
        });
        return found_element;
    }

protected:
    NonElementParentNode() = default;
};

}
