#include "ini.h"
namespace Ini
{
    pair<string_view, string_view> Split(string_view line, char by)
    {
        size_t pos = line.find(by);
        string_view left = line.substr(0, pos);

        if (pos < line.size() && pos + 1 < line.size())
        {
            return {left, line.substr(pos + 1)};
        }
        else
        {
            return {left, string_view()};
        }
    }

    string_view Lstrip(string_view line)
    {
        while (!line.empty() && isspace(line[0]))
        {
            line.remove_prefix(1);
        }
        return line;
    }

    string_view remove_square_braces(string_view value)
    {
        value.remove_prefix(1);
        value.remove_suffix(1);
        return value;
    }

    Section &Document::AddSection(string name)
    {
        return sections[name];
    }
    const Section &Document::GetSection(const string &name) const
    {
        return sections.at(name);
    }
    size_t Document::SectionCount() const
    {
        return sections.size();
    }
    Document Load(istream &input)
    {
        Document doc;
        string_view sec_name;
        Section *section = nullptr;
        for (string line; getline(input, line);)
        {
            if (!line.empty())
            {
                if (line[0] == '[')
                {
                    sec_name = remove_square_braces(line);
                    section = &doc.AddSection(string(sec_name));
                }
                else
                {
                    auto [key, value] = Split(line, '=');
                    section->insert({string(key), string(value)});
                }
            }
        }
        return doc;
    }
}
