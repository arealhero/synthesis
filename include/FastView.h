#pragma once

#include "Element.h"

#include <functional>
#include <set>

namespace synthesis {

struct FastView
{
 public:
  FastView() = default;
  FastView(const FastView&) = default;
  FastView(FastView&&) noexcept = default;

  FastView& operator=(const FastView&) = default;
  FastView& operator=(FastView&&) noexcept = default;

  template<typename Range>
  FastView(Range& elements);

  template<>
  FastView(FastView& elements);

  void Add(Element* element);
  void Remove(Element* element);

  Element* Find(const char* name) const;

  [[nodiscard]] int Count() const;
  [[nodiscard]] Element* Get(int i) const;

 private:
  using Comparator = std::function<bool(const Element*, const Element*)>;
  static inline bool ElementComparator(const Element* lhs, const Element* rhs)
  {
    return lhs->name < rhs->name;
  }

  std::set<Element*, Comparator> elements{ &ElementComparator };
};

}
