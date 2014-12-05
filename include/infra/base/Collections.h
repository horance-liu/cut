#ifndef H65A42ECE_C860_4B18_A566_30A7D4404D40
#define H65A42ECE_C860_4B18_A566_30A7D4404D40

template <typename C>
void clear_container(C& container)
{
    for (auto e : container)
    {
        delete e;
    }

    container.clear();
}

#endif
