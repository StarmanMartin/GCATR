//
// Created by Martin on 18.07.2018.
//

#ifndef GCATCPP_EDGE_H
#define GCATCPP_EDGE_H

#include <string>
#include <memory>

#include "../codes/Alphabet.h"


namespace graph {
    class Vertex;

    class Edge {
    public:
        Edge(std::shared_ptr<Vertex> from, std::shared_ptr<Vertex> to, Alphabet alAlphabet);

        std::string get_label() const;

        int get_index() const;

        std::shared_ptr<Vertex> get_from() const;
        std::shared_ptr<Vertex> get_to() const;

        explicit operator std::string() const { return this->get_label(); }

        friend std::ostream &operator<<(std::ostream &_stream, Edge const &mc) {
            _stream << mc.get_label();
            return _stream;
        }

        int compare(const Edge &) const;

        bool operator==(const Edge &d) const { return !this->compare(d); }

        bool operator<(const Edge &d) const { return compare(d) < 0; }

        bool operator>(const Edge &d) const { return compare(d) > 0; }

        bool operator>>(const Vertex &d) const;
        bool operator<<(const Vertex &d) const;

    private:
        std::shared_ptr<Vertex> from;
        std::shared_ptr<Vertex> to;
        Alphabet alphabet;
        int index;

        std::string label;

        void calculate_index();
    };
}


#endif //GCATCPP_EDGE_H
