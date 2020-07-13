#include <FastView.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>

namespace synthesis {

template<typename Range>
FastView::FastView(Range& elements)
{
  for (auto& element : elements) {
    Add(element);
  }
}

FastView::FastView(FastView& elements)
  : FastView(elements.elements)
{}

void FastView::Add(Element* element)
{
  elements.insert(element);
}

void FastView::Remove(Element* element)
{
  elements.erase(element);
}

std::vector<Element*> FastView::Find(const std::string& name, bool isCaseSensitive) const
{
  std::vector<Element*> found;

  auto comparator = [&isCaseSensitive](unsigned char lhs, unsigned char rhs) {
    return isCaseSensitive ? (lhs == rhs) : (std::toupper(lhs) == std::toupper(rhs));
  };

  for (auto& element : elements) {
    auto filename = element->name;
    auto it = std::search(filename.begin(), filename.end(), name.begin(), name.end(), comparator);

    if (it != filename.end()) {
      found.push_back(element);
    }
  }

  return found;
}

int FastView::Count() const
{
  return elements.size();
}

Element* FastView::Get(int i) const
{
  auto it = elements.begin();
  std::advance(it, i);
  return *it;
}

}
