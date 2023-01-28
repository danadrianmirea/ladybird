/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/UIEvents/UIEvent.h>

namespace Web::UIEvents {

UIEvent* UIEvent::create(JS::Realm& realm, DeprecatedFlyString const& event_name)
{
    return realm.heap().allocate<UIEvent>(realm, realm, event_name).release_allocated_value_but_fixme_should_propagate_errors();
}

UIEvent* UIEvent::construct_impl(JS::Realm& realm, DeprecatedFlyString const& event_name, UIEventInit const& event_init)
{
    return realm.heap().allocate<UIEvent>(realm, realm, event_name, event_init).release_allocated_value_but_fixme_should_propagate_errors();
}

UIEvent::UIEvent(JS::Realm& realm, DeprecatedFlyString const& event_name)
    : Event(realm, event_name)
{
}

UIEvent::UIEvent(JS::Realm& realm, DeprecatedFlyString const& event_name, UIEventInit const& event_init)
    : Event(realm, event_name, event_init)
    , m_view(event_init.view)
    , m_detail(event_init.detail)
{
}

UIEvent::~UIEvent() = default;

JS::ThrowCompletionOr<void> UIEvent::initialize(JS::Realm& realm)
{
    MUST_OR_THROW_OOM(Base::initialize(realm));
    set_prototype(&Bindings::ensure_web_prototype<Bindings::UIEventPrototype>(realm, "UIEvent"));

    return {};
}

void UIEvent::visit_edges(Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_view.ptr());
}

}
