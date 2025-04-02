#include <vector>
#include <string>
#include <memory>

// StrBlob is a bunch of strings that can be shared among multiple StrBlob objects by using shared_ptr.
class StrBlob {
public:

  typedef std::vector<std::string>::size_type size_type;
  
  StrBlob(): data_(std::make_shared<std::vector<std::string>>()) {}
  
  StrBlob(std::initializer_list<std::string> il): data_(std::make_shared<std::vector<std::string>>(il)) {};
  
  size_type Size() const { return data_->size(); }

  bool Empty() const { return data_->empty(); }

  void PushBack(const std::string &t) { data_->push_back(t); }

  void PopBack();
  
  std::string& Front();

  std::string& Back();
  
private:
  std::shared_ptr<std::vector<std::string>> data_;

  // throws msg if data[i] isn't valid
  void check(size_type i, const std::string &msg) const;
};