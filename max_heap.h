//
//  max_heap.h
//  hw1_pic10c
//
//  Created by Anh Tran on 3/29/22.
//

#ifndef max_heap_h
#define max_heap_h

#include <utility>
#include <vector>
#include <stdexcept>

//defining the max_heap class within the pic10c namespace
namespace pic10c {
    template <typename T, typename compare_type = std::less<T>>
    class max_heap;
}

template <typename T, typename compare_type>
class pic10c::max_heap {
public:

    //Default Constructor, the default compare_type is set to compare_type{}
    max_heap(const compare_type& compare = compare_type{});

    //helper functon for the insert function used to demote the parent value if the new value is larger
    void promote(T foo);

    //overloaded functions that places object into the data structure
    //used for lvalues
    void insert(const T& foo);
    //used for rvalues 
    void insert(const T&& foo);

    //function that returns the number of elements in the structure
    size_t size() const { return values.size(); };
    /*the first element of a max heap is a random number we do not want to touch, so the -1 is there to adjust to the actual size of the heap*/

    //function that returns the "maximum" value froom the heap
    T top() const { return values.front(); };
    /*a vector is 0 indexed and we do not want the first element due to it being a random number so the root node (which is the max value) would be located in the 1 index */

    /*function that removes the "maximum" value from the heap
     throws a logic error if heap is empty */
    void pop();


private:

    std::vector <T> values;
    compare_type pred;

    //returns index of a the parent node
    size_t index_p(size_t i) const { return (i - 1) / 2; };
    //returns the index of the left child
    size_t index_l(size_t i) const { return (2 * i + 1); };
    //returns the index of the right child
    size_t index_r(size_t i) const { return (2 * i + 2); };

    //returns value of parent node
    T get_p(size_t i) const { return values[(i - 1) / 2]; };
    //returns the value of the left child
    T get_l(size_t i) const { return values[2 * i + 1]; };
    //returns the value of the right child
    T get_r(size_t i) const { return values[2 * i + 2]; };

};


template<typename T, typename compare_type>
pic10c::max_heap<T, compare_type>::max_heap(const compare_type& compare) :pred(compare) {}


template<typename T, typename compare_type>
void pic10c::max_heap<T, compare_type>::promote(T foo) {
    size_t i = values.size() - 1;
    while (i > 0 && pred(get_p(i), foo)) {
        values[i] = get_p(i); //assign the parent to the end slots
        i = index_p(i); //the index is now the parent's orginal index
    }

    //store the value into the vacant slot
    values[i] = foo;
}


template<typename T, typename compare_type>
void pic10c::max_heap<T, compare_type>::insert(const T& foo) {

    //push back the value
    values.push_back(std::move(foo));

    //if the parents are lesser than the new value, we demote them
    promote(foo);
}


template<typename T, typename compare_type>
void pic10c::max_heap<T, compare_type>::insert(const T&& foo) {

    //adding a vacant slot to the end
    values.push_back(std::move(foo));

    //if the parents are lesser than the new value, we demote them
    promote(foo);
}


template<typename T, typename compare_type>
void pic10c::max_heap<T, compare_type>::pop() {

    //throwing a logic error if the heap is empty at call, vector size is set to less than 1 because a heap has a random variable in the first slot
    if (values.empty()) {
        throw std::logic_error("pop empty");
    }

    size_t fin_i = values.size() - 1; //set index to the last node
    T last_node = std::move(values[fin_i]); //get the value for the last node
    values.pop_back(); //delete maximum value


    //if the index of the final node is now larger than 0, meaning that it is not a root node, this means there are existing child nodes from the removed root node that is larger than the new root and the new root must be demoted bc heap condition is violated
    if (fin_i > 0)
    {
        values[0] = std::move(last_node); //send the last node to the root node

        //now because the heap condition is violated, the heap needs to be rearranged
        T root_node = std::move(values[0]); //last_node is now the root node
        size_t fin_i = values.size() - 1;

        //create a new index that we can use to promote child nodes
        size_t i = 0;

        //creating an ending condition for the while loop
        bool fin = false;

        //while loop to promote children of deleted root
        while (!fin)
        {
            size_t index_c = std::move(index_l(i));
            if (index_c <= fin_i)
            {
                //start by grabing the left child
                T c = get_l(i);

                //if there is a right child we find the largest child by comparison
                if (index_r(i) <= fin_i && pred(c, get_r(i)))
                {
                    index_c = std::move(index_r(i));
                    c = get_r(i);
                }

                //check to see if root is larger than child, if it is then promote child
                if (pred(root_node, c))
                {
                    using std::swap;
                    swap(c, values[i]);
                    i = std::move(index_c);
                }
                //if root is larger than the children so we assert ending condition
                else
                {
                    fin = true;
                }
            }
            //if there are no children left we assert ending condition
            else
            {
                fin = true;
            }
        }
        values[i] = root_node; //store the value
    }
}

#endif /* max_heap.h */
