//Сделано на семинаре
bool Tree::Has(const std::vector<std::string>& node) const {
    const Node * c = &root;
    for (const auto& i : node) {
        if (c->children.find(i) == c->children.end())
            return false;
        c = &(c->children.at(i));
    }
    return true;
}

void Tree::Insert(const std::vector<std::string>& node) {
    Node * c = &root;
    for (const auto& i : node) {
        if (c->children.find(i) == c->children.end())
            c->children[i] = Node();
        c = &(c->children[i]);
    }
}

void Tree::Delete(const std::vector<std::string>& node) {
    Node * c = &root;
    for (size_t i = 0; i < node.size(); ++i) {
        if (c->children.find(node[i]) == c->children.end())
            return;
        if (i != node.size() - 1)
            c = &(c->children[node[i]]);
    }
    c->children.erase(node[node.size() - 1]);
}