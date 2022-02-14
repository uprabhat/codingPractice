#include <iostream>
#include <string>
#include <memory>

class Entity {
  public:
    Entity() {
      std::cout << "Created entity\n";
    }
    ~Entity() {
      std::cout << "Destroyed entity\n";
    }
    void Print() {
      std::cout<<"Printing Entity\n";
    }
};


int main() {

  {
    //Unqique ptr in scope onlu - no copied
    std::unique_ptr<Entity> e0(new Entity()); //calling the constructor
    std::unique_ptr<Entity> e1 = std::make_unique<Entity>(); //Preferred for exceptions
    //std::unique_ptr<Entity> e2=e1; // Error - not allowed with unique pointers
    e0->Print();
  }
  // unique is deleted


  //shared pointer - keeps a count of references to that object
  std::shared_ptr<Entity> shE1 = std::make_shared<Entity>();
  {
    std::shared_ptr<Entity>  shE0 = std::make_shared<Entity>();
    //std::shared_ptr<Entity>  shE0(new Entity()) ; //Not good - ctrl block not create
    shE1= shE0;
  }
  //std::shared_ptr<Entity> shE1= shE0; //error - out of scope
  //std:weak_ptr<Entity> wkE =shE1; //Weak=pointer doesn't increase ref-count
  shE1->Print();
  

  return 0;
}