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

std::vector<Element*> View::Find(const std::string &name, bool isCaseSensitive) const
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

int View::Count() const
{
  return elements.size();
}

Element* View::Get(int i) const
{
  return elements[i];
}

}
