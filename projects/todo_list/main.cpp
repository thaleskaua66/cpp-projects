#include <iostream>
#include <vector>

class Item
{
  public:
    std::string name;
    bool done = false;
};

void addItem(std::vector<Item> &vector);
void removeItem(std::vector<Item> &vector);
int markDone(std::vector<Item> &vector);

int main()
{
  std::vector<Item> items;
  bool running = true;
  int index;

  do{
    std::cout << "*************************\n";
    std::cout << "******* TODO LIST *******\n";
    std::cout << "*************************\n";

    // printing items
    for(int i = 0; i < items.size(); i++){
      if(items[i].done){
        std::cout << (i + 1) << ". " << items[i].name << " [DONE]\n";
      }else{
        std::cout << (i + 1) << ". " << items[i].name << "\n";
      }
    }

    // printing menu
    int selected;
    std::cout << "\nWhat do you want to do now?\n";
    std::cout << "[1] Insert item\n[2] Delete item\n[3] Mark as done\n[4] Exit\n";
    std::cout << "Select: ";
    std::cin >> selected;

    // Check matching cases
    switch(selected){
      case 1:
        addItem(items);
        break;
      case 2:
        removeItem(items);
        break;
      case 3:
        index = markDone(items);

        if(index < 0 || index > items.size()){
          std::cout << "Item not found.\n";
        }else{
          items[index].done = true;
        }
        
        break;
      case 4:
        running = false;
        break;
      default:
        std::cout << "Invalid option.\n";
    }
  }while(running);
}

void addItem(std::vector<Item> &vector)
{
  Item item_to_add;

  std::cout << "Item to add: ";
  std::cin.ignore();
  std::getline(std::cin, item_to_add.name);

  vector.push_back(item_to_add);
}

void removeItem(std::vector<Item> &vector)
{
  int index;

  std::cout << "Index of the item to remove: ";
  std::cin >> index;

  if(index < 1 || index > vector.size()){
    std::cout << "Item not found.\n";
  }else{
    vector.erase(vector.begin() + (index - 1));
  }
}

int markDone(std::vector<Item> &vector)
{
  int index;

  std::cout << "Index of the item to mark as done: ";
  std::cin >> index;

  return index - 1;
}