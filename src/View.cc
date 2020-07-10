#include <View.h>

#include <algorithm>
#include <memory>

namespace synthesis {

template<typename Range>
View::View(Range& elements)
{
  for (auto& element : elements) {
    Add(element);
  }
}

template<>
View::View(View& elements)
  : View(elements.elements)
{}

void View::Add(Element* element)
{
  auto it = std::lower_bound(elements.begin(), elements.end(), element, ElementComparator);
  elements.insert(it, element);
}

void View::Remove(Element* element)
{
  auto it = std::lower_bound(elements.begin(), elements.end(), element, ElementComparator);
  if (it != elements.end() && (*it) == element) {
    elements.erase(it);
  }
}

Element* View::Find(const char* name) const
{
  auto fakeElement = std::make_shared<Element>(name);
  auto it = std::lower_bound(elements.begin(), elements.end(), fakeElement.get(), ElementComparator);

  if (it == elements.end() || (*it)->name != name) {
    return nullptr;
  }

  return *it;
}

int View::Count() const
{
  return elements.size();
}

Element* View::Get(int i) const
{
  return elements[i];
}

}
