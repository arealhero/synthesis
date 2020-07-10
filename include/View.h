#pragma once

#include "Element.h"

#include <functional>
#include <vector>

namespace synthesis {

struct View
{
 public:
  View() = default;
  View(const View&) = default;
  View(View&&) noexcept = default;

  View& operator=(const View&) = default;
  View& operator=(View&&) noexcept = default;

  template<typename Range>
  View(Range& elements);

  View(View& elements);

  void Add(Element* element);
  void Remove(Element* element);

  Element* Find(const char* name) const;

  [[nodiscard]] int Count() const;
  [[nodiscard]] Element* Get(int i) const;

 private:
  std::vector<Element*> elements;

  static inline bool ElementComparator(const Element* lhs, const Element* rhs)
  {
    return lhs->name < rhs->name;
  }
};

}
