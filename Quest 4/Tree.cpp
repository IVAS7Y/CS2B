// Student ID: 20587063
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Tree.h"
using namespace std;

Tree::Node *Tree::Node::insert_sibling(Node *p)
{
    if (p == nullptr)
    {
        return nullptr;
    }
    if (this->_sibling != nullptr)
    {
        Node *next = this->_sibling;
        while (next != nullptr && next->_sibling != nullptr)
        {
            next = next->_sibling;
        }
        next->_sibling = p;
        return p;
    }
    else
    {
        this->_sibling = p;
        return p;
    }
}

Tree::Node *Tree::Node::insert_child(Node *p)
{
    if (p == nullptr)
    {
        return nullptr;
    }
    if (this->_child == nullptr)
    {
        this->_child = p;
        return p;
    }
    else
    {
        return this->_child->insert_sibling(p);
    }
}

const Tree::Node &Tree::Node::operator=(const Tree::Node &that)
{
    if (this != &that)
    {

        _data = that._data;
        if (that._child != nullptr)
        {
            _child = new Node(*that._child);
        }
        else
        {
            _child = nullptr;
        }
        if (that._sibling != nullptr)
        {
            _sibling = new Node(*that._sibling);
        }
        else
        {
            _sibling = nullptr;
        }

        return *this;

        // this->_sibling = new Node(that._sibling->get_data());
        // this->_child = new Node(that._child->get_data());
        return *this;
    }
    return *this;
}

Tree::Node::Node(const Node &that)
{
    *this = that;
}
bool Tree::Node::is_equal(const Node *p1, const Node *p2)
{
    if (p1 == nullptr && p2 == nullptr)
        return true;
    if (p1 == nullptr || p2 == nullptr)
        return false;
    if (p1->_data != p2->_data)
        return false;
    if (!is_equal(p1->_child, p2->_child))
        return false;
    return is_equal(p1->_sibling, p2->_sibling);
}

bool Tree::Node::operator==(const Node &that) const
{
    return is_equal(this, &that);
}

bool Tree::Node::operator!=(const Node &that) const
{
    return !(*this == that);
}

string Tree::Node::to_string() const
{
    ostringstream oss;
    oss << this->get_data() << " :";
    Node *next = this->_child;
    while (next != nullptr)
    {
        oss << " " << next->get_data();
        next = next->_sibling;
    }
    oss << "\n";
    next = this->_child;
    if (next != nullptr)
    {
        oss << "# Child of " << this->get_data() << "\n";
        oss << next->to_string();
        next = next->_sibling;
    }
    next = this->_sibling;
    if (next)
    {
        oss << "# Next sib of " << this->get_data() << "\n";
        oss << next->to_string();
        next = next->_sibling;
    }
    return oss.str();
}

Tree::Node::~Node()
{
    if (this->_child)
    {
        delete this->_child;
        this->_child = nullptr;
    }
    if (this->_sibling)
    {
        delete this->_sibling;
        this->_sibling = nullptr;
    }
}

Tree::Tree()
{
    _root = new Node("ROOT");
}

Tree::~Tree()
{
    delete _root;
    _root = nullptr;
}

Tree &Tree::operator=(const Tree &that)
{
    if (this != &that)
    {
        _root = new Node(*that._root);
    }
    return *this;
}

Tree::Tree(const Tree &that)
{
    if (this != &that)
    {
        *this = that;
    }
}

bool Tree::operator==(const Tree &that) const
{
    return Node::is_equal(this->_root, that._root);
}
bool Tree::operator!=(const Tree &that) const
{
    return !(*this == that);
}

string Tree::to_string() const
{
    ostringstream oss;
    oss << "# Tree rooted at " << _root->get_data() << "\n";
    oss << "# The following lines are of the form:"
        << "\n";
    oss << "#   node: child1 child2...\n";
    oss << _root->to_string();
    oss << "# End of Tree"
        << "\n";
    return oss.str();
}

void Tree::make_special_config_1(const vector<string> &names)
{
    // Delete any existing tree structure
    delete _root;
    _root = nullptr;

    // Create the root node
    _root = new Node("ROOT");

    // Create the first level of siblings
    Node *current = _root;
    for (int i = 0; i < 4; i++)
    {
        _root->insert_sibling(new Node(names[i]));
    }
    current = current->_sibling;
    for (int i = 4; i < 6; i++)
    {
        current->insert_child(new Node(names[i]));
    }

    current = current->_sibling;
    for (int i = 6; i < 8; i++)
    {
        current->insert_child(new Node(names[i]));
    }

    current = current->_sibling;
    for (int i = 8; i < 10; i++)
    {
        current->insert_child(new Node(names[i]));
    }

    current = current->_sibling;
    for (int i = 10; i < 12; i++)
    {
        current->insert_child(new Node(names[i]));
    }

    current = _root->_sibling;
    current->_child->insert_child(new Node(names[12]));
    current->_child->_sibling->insert_child(new Node(names[13]));

    current = _root->_sibling->_sibling;
    current->_child->insert_child(new Node(names[14]));
    current->_child->_sibling->insert_child(new Node(names[15]));

    current = _root->_sibling->_sibling->_sibling;
    current->_child->insert_child(new Node(names[16]));
    current->_child->_sibling->insert_child(new Node(names[17]));
        
    current = _root->_sibling->_sibling->_sibling->_sibling;
    current->_child->insert_child(new Node(names[18]));
    current->_child->_sibling->insert_child(new Node(names[19]));
}

ostream &operator<<(std::ostream &os, const Tree &tree)
{
    os << tree.to_string();
    return os;
}