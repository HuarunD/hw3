#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>

#include <vector>// need 
template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  int child_;
  std::vector<T> data_;
	PComparator c_;


};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c):child_(m),c_(c){

}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
	data_.push_back(item);
	std::size_t index = data_.size() - 1;
	while(index!=0){
    std::size_t parent_index = (index - 1) / child_;
    T& current = data_[index];
    T& parent = data_[parent_index];
    if (c_(current,parent)) {// need change 
      std::swap(current, parent);
     	index = parent_index;	
		}
		else{
			break;
		}	
	}
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
	return data_[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
		// ================================
    throw std::out_of_range("heap is empty");

  }
	data_[0] = data_[data_.size()-1];
	data_.pop_back();
	bool done_ = false;
	int index = 0;
	while(!done_){
		if(child_*index +1 >= data_.size()){
			done_ = true;
		}
		else if( child_*index +child_ >= data_.size()){// less than child_ childs
			size_t remain_ =  data_.size() - child_*index - 1;
			for(unsigned int i=1 ; i<=remain_; i++){
				if(!c_(data_[index],data_[child_*index+i])){//need change
					done_ = false;
					break;
				}
				if(i==remain_){// can be risky
					done_ = true;
				}
			}
			size_t chosen_child = child_*index+1;
			if(!done_){
				for(unsigned int i=1 ; i<=remain_; i++){
					if(!c_(data_[chosen_child],data_[child_*index+i])){//need change
						chosen_child = child_*index+i;
					}				
				}
				T& current = data_[index];
        T& child = data_[chosen_child];
        std::swap(current, child);
				index = chosen_child;
			}
		}
		else{// have child_ childs 
			for(unsigned int i=1 ; i<=child_; i++){
				if(!c_(data_[index],data_[child_*index+i])){//need change
					done_ = false;
					break;
				}
				if(i==child_){// can be risky
					done_ = true;
				}
			}
			size_t chosen_child = child_*index+1;
			if(!done_){
				for(unsigned int i=1 ; i<=child_; i++){
					if(!c_(data_[chosen_child],data_[child_*index+i])){//need change
						chosen_child = child_*index+i;
					}				
				}
				T& current = data_[index];
        T& child = data_[chosen_child];
        std::swap(current, child);
				index = chosen_child;
			}
		}
	}
		


}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
	return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
	return data_.size();
}
#endif