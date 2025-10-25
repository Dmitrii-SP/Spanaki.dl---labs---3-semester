bool init(subforwardlist** sfl) {
    *sfl = nullptr;
    return true;
}

bool push_back(subforwardlist** sfl, int d) {
    subforwardlist* const n = new subforwardlist;
    n->data = d;
    n->next = nullptr;
    
    subforwardlist** p = sfl;
    while ( *p != nullptr ) {
        p = &(*p)->next;
    }
    *p = n;
    
    return true;
}

int pop_back(subforwardlist** sfl) {
    if ( *sfl == nullptr ) return 0;
    
    subforwardlist** p = sfl;
    while ( (*p)->next != nullptr ) {
        p = &(*p)->next;
    }
    
    subforwardlist* z = *p; 
    const int val = z->data;
    *p = nullptr;
    delete z;
    
    return val;
}

bool push_forward(subforwardlist** sfl, int d) {
    subforwardlist* const n = new subforwardlist;
    n->data = d;
    n->next = *sfl;
    *sfl = n;
    
    return true;
}

int pop_forward(subforwardlist** sfl) {
    if ( *sfl == nullptr ) return 0;
    
    subforwardlist* const r = *sfl;
    const int val = r->data;
    *sfl = r->next;
    delete r;
    
    return val;
}

bool push_where(subforwardlist** sfl, unsigned int where, int d) {
    subforwardlist** p = sfl;
    
    for ( unsigned int idx = 0; idx < where; ++idx ) {
        if ( *p == nullptr ) return false;
        p = &(*p)->next;
    }
    
    subforwardlist* const n = new subforwardlist;
    n->data = d;
    n->next = *p;
    *p = n;
    
    return true;
}

int erase_where(subforwardlist** sfl, unsigned int where) {
    subforwardlist** p = sfl;
    
    for ( unsigned int x = 0; x < where; ++x ) {
        if ( *p == nullptr ) return 0;
        p = &(*p)->next;
    }
    
    if ( *p == nullptr ) return 0;
    
    subforwardlist* const e = *p;
    const int val = e->data;
    *p = e->next;
    delete e;
    
    return val;
}

unsigned int size(subforwardlist** sfl) {
    unsigned int len = 0;
    subforwardlist* iter = *sfl;
    
    if ( iter != nullptr ) {
        do {
            len++;
            iter = iter->next;
        } while ( iter != nullptr );
    }
    
    return len;
}

void clear(subforwardlist** sfl) {
    while ( true ) {
        if ( *sfl == nullptr ) break;
        
        subforwardlist* const t = *sfl;
        *sfl = (*sfl)->next;
        delete t;
    }
}