//
// Created by Martin on 18.07.2018.
//

#ifndef GCATCPP_VERTEX_H
#define GCATCPP_VERTEX_H

#include <string>
namespace graph {
    class Vertex {
    public:
        Vertex(std::string label);

        std::string get_label() const;

        int get_index() const;

        operator std::string() const { return this->get_label(); }

        friend std::ostream &operator<<(std::ostream &_stream, Vertex const &mc) {
            _stream << mc.get_label();
            return _stream;
        }

        int compare(const Vertex &) const;

        bool operator==(const Vertex &d) const { return !this->compare(d); }

        bool operator<(const Vertex &d) const { return compare(d) < 0; }

        bool operator>(const Vertex &d) const { return compare(d) > 0; }


    private:
        std::string label;
        int index;

        void calculate_index();
    };
}

#endif //GCATCPP_VERTEX_H
