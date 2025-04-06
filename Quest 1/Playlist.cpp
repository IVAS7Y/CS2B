// Student ID: 20587063
#include "Playlist.h"
using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

bool Playlist::Song_Entry::set_id(int id)
{
    if (id >= 0)
    {
        _id = id;
        return true;
    }
    return false;
}
bool Playlist::Song_Entry::set_name(string name)
{
    if (name != "")
    {
        _name = name;
        return true;
    }
    return false;
}

Playlist::Playlist()
{

    Song_Entry head(-1, "HEAD");
    _head = new Node(head);
    _tail = _head;
    _prev_to_current = _head;
    _size = 0;
}

Playlist::~Playlist()
{
    Node *curr = _head->get_next();
    while (curr != nullptr)
    {
        Node *next = curr->get_next();
        delete curr;
        curr = next;
    }
    delete _head;
}

Playlist::Node::~Node()
{

}

Playlist *Playlist::insert_at_cursor(const Song_Entry &s)
{
    Node *tmp = _prev_to_current->get_next();
    _prev_to_current->insert_next(new Node(s));
    if (tmp == nullptr) { // if the cursor is at the end of the list
        _tail = _prev_to_current->get_next();
    }

    _size++;

    return this;
}

Playlist *Playlist::push_back(const Song_Entry &s)
{
    Node *tmp = _prev_to_current;
    _prev_to_current = _tail;
    insert_at_cursor(s);
    _tail = _prev_to_current->get_next();
    _prev_to_current = tmp;
    return this;
}

Playlist *Playlist::push_front(const Song_Entry &s)
{
    Node *tmp = _prev_to_current;
    _prev_to_current = _head;
    insert_at_cursor(s);
    _prev_to_current = tmp;
    return this;
}

Playlist *Playlist::advance_cursor()
{
    if (_prev_to_current == _tail)
    {
        return nullptr;
    }

    _prev_to_current = _prev_to_current->get_next();
    return this;
}

Playlist *Playlist::circular_advance_cursor()
{
    if (_prev_to_current->get_next() == _tail)
    {
        _prev_to_current = _head;
        return this;
    }
    return advance_cursor();
}

Playlist::Song_Entry &Playlist::get_current_song() const
{
    if (_prev_to_current == _tail)
    {
        return _head->get_song();
    }
    else
    {
        return _prev_to_current->get_next()->get_song();
    }
}

Playlist *Playlist::remove_at_cursor()
{
    if (_prev_to_current->get_next() == nullptr) {
        return this;
    }

    Node *tmp = _prev_to_current->get_next();
    _prev_to_current->remove_next();

    if (tmp == _tail) {
        _tail = _prev_to_current;
    }

    _size--;

    return this;
}

size_t Playlist::get_size() const
{
    return _size;
}

Playlist *Playlist::rewind()
{
    _prev_to_current = _head;
    return this;
}

Playlist *Playlist::clear()
{
    while (_head->get_next() != nullptr) {
        _head->remove_next();
    }

    _tail = _head;
    _prev_to_current = _head;
    _size = 0;

    return this;
}

Playlist::Song_Entry &Playlist::find_by_id(int id) const
{
    Node *temp = _head->get_next();
    while (temp != nullptr)
    {
        if (temp->get_song().get_id() == id)
        {
            return temp->get_song();
        }
        temp = temp->get_next();
    }
    return _head->get_song();
}

Playlist::Song_Entry &Playlist::find_by_name(string id) const
{
    Node *temp = _head->get_next();
    while (temp != nullptr)
    {
        if (temp->get_song().get_name() == id)
        {
            return temp->get_song();
        }
        temp = temp->get_next();
    }
    return _head->get_song();
}

string Playlist::to_string() const
{
    std::ostringstream oss;
    oss << "Playlist: " << get_size() << " entries.\n";
    Node *temp = _head->get_next();
    size_t i;
    if (get_size() < 25)
    {
        i = get_size();
    }
    else
    {
        i = 25;
    }
    for (size_t j = 0; j < i; j++)
    {
        oss << "{ id: " << temp->get_song().get_id() << ", name: " << temp->get_song().get_name() << " }";
        if (temp == _prev_to_current)
        {
            oss << " [P]\n";
        }
        else if (temp == _tail)
        {
            oss << " [T]\n";
        }
        else
        {
            oss << "\n";
        }
        temp = temp->get_next();
    }
    if(get_size() > 25){
        oss << "...\n";
    }

    return oss.str();
}

Playlist::Node *Playlist::Node::insert_next(Node *p) {
    Node *tmp = _next;

    _next = p;
    _next->_next = tmp;

    return p;
}

Playlist::Node *Playlist::Node::remove_next() {
    if (_next == nullptr) {
        return nullptr; 
    }
    Node *tmp = _next;
    _next = _next->_next;
    delete tmp;

    return this;
}