#include <FastView.h>

#include <algorithm>
#include <iterator>

namespace synthesis {

template<typename Range>
FastView::FastView(Range& elements)
{
  for (auto& element : elements) {
    Add(element);
  }
}

template<>
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

Element* FastView::Find(const char* name) const
{
  auto fakeElement = std::make_shared<Element>(name);
  auto it = elements.find(fakeElement.get());

  if (it == elements.end()) {
    return nullptr;
  }

  return *it;
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
