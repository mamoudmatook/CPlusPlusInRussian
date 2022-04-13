class SortedStrings {
public:
  void AddString(const string& s) {
    // добавить строку s в набор
    lines.push_back(s);
  }
  vector<string> GetSortedStrings() {
    // получить набор из всех добавленных строк в отсортированном порядке
    sort(lines.begin(),lines.end());
    return lines;
  }
private:
  // приватные поля
  vector <string> lines;
};