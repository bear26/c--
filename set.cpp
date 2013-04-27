#define BOOST_TEST_MODUILE test_module
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <iostream>
using namespace std;
struct pt
{
  int value;
	pt* l;
	pt* r;
	pt* t;
	pt()
	{
	}
	~pt(){}
};

struct set
{
private:
    pt* head=new pt;
    pt* tail=new pt;
	int size;
	void delet(pt* q)
	{
        if (q->l->l!=nullptr)
			delet(q->l);
        if (q->r->l!=nullptr)
			delet(q->r);
        q->l=q->r=q->t=0;
		delete q;		
	}
    void copy(pt* s)
	{
        this->insert(s->value);
        if (s->l->l!=nullptr)
            copy(s->l);
        if (s->r->l!=nullptr)
            copy(s->r);
		return ;
	}
public:
	set()
	{
		this->tail->l=nullptr;
		this->tail->r=nullptr;
		this->tail->t=head;
		this->size=0;
	}
	set(set const& q)
	{
        this->head->value=q.head->value;
        this->head->l=this->tail;
        this->head->r=this->tail;
        this->head->t=this->tail;
        this->tail->l=nullptr;
        this->tail->r=nullptr;
        this->tail->t=this->head;
        this->size=q.size;
		this->operator = (q);
	}
	set& operator =(set const& q)
	{
        this->copy(q.head);
		return *this;
	}
	int size1()
	{
		return this->size;
	}
	void insert(int a)
	{
		if (size==0)
		{
            this->head->l=this->tail;
            this->head->r=this->tail;
            this->head->t=this->tail;
            this->head->value=a;
			size++;
			return ;
		}
		pt* v;
        v=this->head;
		while(1)
		{
			if (v->value==a)break;
			if (v->value>a)
			{
                if (v->l!=this->tail)
				{
					v=v->l;
					continue;
				}
				else
				{
					pt* q=new pt;
                    q->l=this->tail;
                    q->r=this->tail;
					q->t=v;
					q->value=a;
					v->l=q;
					size++;
					break;
				}
			}	
			if (v->value<a)
			{
				if (v->r!=tail)
				{
					v=v->r;
					continue;
				}
				else
				{
					pt* q=new pt;
                    q->l=this->tail;
                    q->r=this->tail;
					q->t=v;
					q->value=a;
					v->r=q;
					size++;
					break;
				}
			}
		}
	}
	
	struct iterator
	{

		pt* k;
		iterator (pt* a)
		{
			this->k=a;
		}
		iterator& operator ++()
		{
			if (k->r->l!=nullptr)
			{
				k=k->r;
				while(k->l->l!=nullptr)
					k=k->l;
				return *this;
			}else
			{
				while(k->t->l!=nullptr && k->t->r==k)
					k=k->t;
				if (k->t->l==nullptr)
				{
					while(k->r->l!=nullptr)
						k=k->r;
					this->k=this->k->l;
					return *this;
				}
				k=k->t;
				return *this;
			}			
		}
		iterator operator ++(int)
		{
			if (k->r->l!=nullptr)
			{
				k=k->r;
				while(k->l->l!=nullptr)
					k=k->l;
				return *this;
			}else
			{
				while(k->t->l!=nullptr && k->t->r==k)
					k=k->t;
				if (k->t->l==nullptr)
				{
					while(k->r->l!=nullptr)
						k=k->r;
					this->k=this->k->l;
					return *this;
				}
				k=k->t;
				return *this;
			}			
		}
		iterator& operator --()
		{
            if (this->k->l==nullptr)// tail
            {
                this->k=this->k->t;// head
                while(this->k->r->l!=nullptr)
                    this->k=this->k->r;
                return *this;
            }
            if (this->k->l->l!=nullptr)// go left
            {
                this->k=this->k->l;
                while(this->k->r->l!=nullptr)
                    this->k=this->k->r;
                return *this;
            }else// go up to not right
            {
                while(this->k->t->l==this->k)
                    this->k=this->k->t;
                this->k=this->k->t;
                return *this;
            }
			
		}
		iterator operator --(int)
		{
            if (this->k->l==nullptr)// tail
			{
                this->k=this->k->t;// head
                while(this->k->r->l!=nullptr)
                    this->k=this->k->r;
				return *this;
			}
            if (this->k->l->l!=nullptr)// go left
			{
                this->k=this->k->l;
                while(this->k->r->l!=nullptr)
                    this->k=this->k->r;
				return *this;
            }else// go up to not right
			{
                while(this->k->t->l==this->k)
                    this->k=this->k->t;
                this->k=this->k->t;
				return *this;
            }
		}
		int& operator*() const
		{
			return k->value;
		}
		bool operator==(iterator const& q) const
		{
			return q.k==this->k;
		}
		bool operator!=(iterator const& q) const
		{
			return q.k!=this->k;
		}
		~iterator(){}
		
	};
	iterator find(int a)
	{
		pt* v=head;
		if (size==0)return end();
 		//if (head->value==a)return iterator(head);
		//v=head;
		while(1)
		{
			if (v->value==a)return iterator(v);else
			if (v->value>a)
			{
				if (v->l->l!=nullptr)
					v=v->l;
				else
					return end();
			}else
			if (v->value<a)
			{
				if (v->r->l!=nullptr)
					v=v->r;
				else
					return end();
			}				
		}
		
	}
	void erase(iterator a)
	{
		if ((a.k->l==nullptr && a.k->r==nullptr)||(size==0))return ;
		if (a.k->l==tail && a.k->r==tail)
		{
			if (a.k->t==tail){delete a.k;size--;return ;}
			if (a.k->t->l==a.k)
			{
				a.k->t->l=tail;
				delete a.k;
			}else
			{
				a.k->t->r=tail;
				delete a.k;
			}
			size--;
			return ;
		}
		else
		{
		iterator b=a;
		b++;
		swap(a.k->value,b.k->value);
		erase(b);
		}
		return ;
	}
	iterator begin()
	{
		pt* v;
		v=head;
		while(v->l!=tail)
			v=v->l;
		return iterator(v);
	}
	iterator end()
	{
        return iterator(this->tail);
	}
	~set()
	{
        delet(this->head);
        this->tail->t=0;
        delete this->tail;
	
	}
};
BOOST_AUTO_TEST_CASE(insert){
	// insert() + iterator::operator++(int) + begin() + end() + iterator::end() + iterator::operator* + iterator::operator!=
	set t;
	std::ostringstream s, s2;
	for(int i = 0; i < 100; i++){
		t.insert(i);
		s << i << " ";
	}
	for(set::iterator it = t.begin(); it != t.end(); it++){
		s2 << *it << " ";
	}
    BOOST_CHECK_EQUAL(s.str(), s2.str());
}

BOOST_AUTO_TEST_CASE(erase){
	// erase + find + operator= + iterator::operator++() + set(set const&)
	set t;
	for(int i = 0; i < 100; i++){
		t.insert(i);
	}
    set t2 = t;
	BOOST_CHECK_EQUAL(t.find(50) != t.end(), true);
	t.erase(t.find(50));
	BOOST_CHECK_EQUAL(t.find(50) != t.end(), false);
    BOOST_CHECK_EQUAL(t2.find(50) != t.end(), true);
    set t3(t2);
    set::iterator it = t2.begin();
    ++it;
    t2.erase(it);
    BOOST_CHECK_EQUAL(*(++t2.begin()) != *(++t3.begin()), true);
}

BOOST_AUTO_TEST_CASE(decrement_iterator){
	//iterator::operator--(int) + iterator::operator--() + iterator::operator==
	set t;
	for(int i = 0; i < 100; i++){
		t.insert(i);
	}
	set::iterator it = t.end();
    for(int i = 0; i < 100; i++){
		if(i % 2){
            --it;
		} else {
            it--;
		}
	}
	BOOST_CHECK_EQUAL(it == t.begin(), true);
}

