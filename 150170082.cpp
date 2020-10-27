#include <iostream>
using namespace std;
/* 
Name: Arda Cüce
Number: 150170082
Date: 05.04.2020


Hocam hepsini tek dosyada yaptım, data ödevlerinin birinde ödevi veren hocamıza sorduğumda hepsini tek dosyada yparsanız okumam daha rahat oluyor demişti o nedenle. Kolay Gelsin
iyi çalışmalar.
*/


const int MAX_INGRIDIENT_AMOUNT = 6; // this isn't used to store ingridients, it is to keep which ingridients will be removed, ignridients and drinks alike are stored dynamically using linked lists.

struct StringNode // this data type turned out to hold ingridients only
{
    string data;
    int number; // ingridient indice
    StringNode* next;
    StringNode(string);
};

StringNode::StringNode(string node_data) 
{
    data = node_data;
}

struct Drinks
{
    string drink_name;
    int amount;
    Drinks* next;
    Drinks(string drink_name, int drink_amount);
};


Drinks::Drinks(string in_drink_name, int drink_amount)
{
    drink_name = in_drink_name;
    amount = drink_amount;
    next = NULL;
}

class LinkedList;
class Order;

class Pizza
{
    friend class LinkedList;
    string name;
    string size;
    string crust_type;
    LinkedList* ingridients_list;
   
public:
    Pizza* next;
    Pizza();
    Pizza(string size, string crust_type, int pizza_type);
    Pizza(const Pizza&);
    ~Pizza();
    void print_ingridients() const;

    string inline get_size() const
    {
        return size;
    }
    string inline get_crust_type() const
    {
        return crust_type;
    }
    string inline get_name() const
    {
        return name;
    }
    LinkedList* get_ingridients_list();
};

class LinkedList  // linked list class used to create pizza, stringnode and drinks linked lists.
{
    Pizza* pizza_head;
    StringNode* StringNode_head;
    Drinks* drinks_head;
public:

    void add(StringNode*);
    void add(Pizza*);
    void add(Drinks*);

    void remove_str(int);

    inline Pizza* get_pizza_head()
    {
        return pizza_head;
    }
    inline StringNode* get_string_node_head()
    {
        return StringNode_head;
    }

    inline Drinks* get_drinks_head()
    {
        return drinks_head;
    }

    void inline set_drinks_head(Drinks* d)
    {
        drinks_head = d;
    }

    ~LinkedList();
    LinkedList(StringNode*);
    LinkedList(Pizza*);
    LinkedList(Drinks*);
};

class Order
{
    friend class LinkedList;
    string customer_name;
    LinkedList* pizzas_list;
    LinkedList* drinks_list;
public:
    Order* next;
    Order(string, Pizza*, Drinks*); 
    Order(string, Pizza*);
    ~Order();

    float get_price();
    void print_order();
    void change_name(string);

    string inline get_name()
    {
        return customer_name;
    }

    void inline add_drink(Drinks* d)
    {
        drinks_list -> add(d);
    }
    void inline add_pizza(Pizza* p)
    {
        pizzas_list -> add(p);
    }    
};

class OrderList
{
    int number_of_orders;
    Order* orders_head;
public:
    OrderList();
    ~OrderList();
    void take_order();
    void list_orders();
    void deliver_orders();

};

LinkedList::LinkedList(Pizza* p)
{
    pizza_head = p;
    StringNode_head = NULL;
    drinks_head = NULL;
    p -> next = NULL;
}

LinkedList::LinkedList(StringNode* s)
{
    StringNode_head = s;
    s->number = 1;  // when listing the ingidients, it is used
    pizza_head = NULL;
    drinks_head = NULL;
    s -> next = NULL;
}

LinkedList::LinkedList(Drinks* d)
{
    drinks_head = d;
    d->next=NULL;
    StringNode_head = NULL;
    pizza_head = NULL;
}

LinkedList::~LinkedList()
{
    if(pizza_head) // if it is a Pizza type linked list and so on.
    {
        Pizza *iter=pizza_head, *temp = pizza_head;
        while(iter)
        {
            iter = iter ->next;
            delete temp;
            temp = iter;
        }
    }
    if(drinks_head)
    {
        Drinks *iter=drinks_head, *temp = drinks_head;
        while(iter)
        {
            iter = iter ->next;
            delete temp;
            temp = iter;
        }
    }
    if(StringNode_head)
    {
        StringNode *iter=StringNode_head, *temp = StringNode_head;
        while(iter)
        {
            iter = iter ->next;
            delete temp;
            temp = iter;
        }
    }
}


void LinkedList::add(Pizza* p)
{
    p->next = NULL;

    if (pizza_head == NULL) {   // if we are adding the first node, this situation does not accur in my implementation but i added this just to be safe
        pizza_head = p;
        return;
    }

    Pizza* iter = pizza_head;

    while(iter)
    {
        if(iter -> next == NULL)
        {
            iter -> next = p;
            return;
        }
        iter = iter -> next;
    }
}

void LinkedList::add(StringNode* s)
{
    s->next = NULL;

    if(StringNode_head == NULL)
    {
        StringNode_head = s;
        s -> number = 1;
        return;
    }

    StringNode* iter = StringNode_head;
    int counter = 1;
    while(iter)
    {
        counter++;
        if(iter -> next == NULL)
        {
            
            iter -> next = s;
            s -> number = counter;
            return;
        }
        iter = iter -> next;

    }
}

void LinkedList::add(Drinks *in_drink)
{
    in_drink ->next = NULL;
    if(drinks_head == NULL)
    {
        drinks_head = in_drink;
        in_drink ->next = NULL;
        return;
    }
    Drinks* iter = drinks_head;
    while(iter)
    {
        if(iter -> next == NULL)
        {
            iter -> next = in_drink;
            return;
        }
        iter = iter -> next;
    }
}

void LinkedList::remove_str(int in)
{
    StringNode* iter = StringNode_head; //initialize with head of ingridients list

    if(iter->number == in) //if we want to remove mozarella
    {
        StringNode_head = iter -> next; // change head to head's next
        delete iter;
        return;
    }

    while(iter)
    {
        if((iter -> next)->number == in)
        {
            StringNode* temp = (iter -> next) -> next; // holding the next of the node to be deleted to not lose it
            delete (iter -> next);
            iter -> next = temp;
            return;
        }
        iter = iter -> next;
    }

}

Pizza::Pizza()
{
    name = "margharita";
    size = "medium";
    crust_type = "normal";

    StringNode* ingridient = new StringNode("mozarella");

    ingridients_list = new LinkedList(ingridient);
}

Pizza::Pizza(string in_size, string in_crust_type, int pizza_type)
{

    size = in_size;
    crust_type = in_crust_type;

    StringNode* ingridient = new StringNode("mozarella");

    ingridients_list = new LinkedList(ingridient); // initialize ingridients list with mozarella

    if(pizza_type == 1)
    {
        name = "Chicken Pizza";

        StringNode* chicken_ingridient = new StringNode("chicken"); // create and add ingridients
        StringNode* corn_ingridient = new StringNode("corn");
        StringNode* mushroom_ingridient = new StringNode("mushroom");
        StringNode* onion_ingridient = new StringNode("onion");
        StringNode* tomato_ingridient = new StringNode("tomato");

        ingridients_list -> add(chicken_ingridient);
        ingridients_list ->add(corn_ingridient);
        ingridients_list ->add(mushroom_ingridient);
        ingridients_list ->add(onion_ingridient);
        ingridients_list ->add(tomato_ingridient);

    }
    if(pizza_type == 2 )
    {
        name = "Broccoli Pizza";

        StringNode* broccoli_ingridient = new StringNode("broccoli");
        StringNode* pepperoni_ingridient = new StringNode("pepperoni");
        StringNode* olive_ingridient = new StringNode("olive");
        StringNode* corn_ingridient = new StringNode("corn");     
        StringNode* onion_ingridient = new StringNode("onion");

        ingridients_list -> add(broccoli_ingridient);        
        ingridients_list -> add(pepperoni_ingridient);
        ingridients_list -> add(olive_ingridient);
        ingridients_list -> add(corn_ingridient);
        ingridients_list -> add(onion_ingridient);
    }
    if(pizza_type == 3)
    {
        name = "Sausage Pizza";

        StringNode* sausage_ingridient = new StringNode("sausage");
        StringNode* tomato_ingridient = new StringNode("tomato");
        StringNode* olive_ingridient = new StringNode("olive");
        StringNode* mushroom_ingridient = new StringNode("mushroom");                      
        StringNode* corn_ingridient = new StringNode("corn");

        ingridients_list -> add(sausage_ingridient);
        ingridients_list -> add(tomato_ingridient);
        ingridients_list -> add(olive_ingridient);
        ingridients_list -> add(mushroom_ingridient);
        ingridients_list -> add(corn_ingridient);    
    }
}

Pizza::Pizza(const Pizza& in_pizza)
{
    name = in_pizza.name;
    size = in_pizza.size;
    crust_type = in_pizza.crust_type;

    cout <<"Please enter the number of ingridient you want removed from your pizza." << endl;
    in_pizza.print_ingridients();
    cout <<"Press 0 to save it" << endl;


    StringNode* ingridient = new StringNode("mozarella");

    ingridients_list = new LinkedList(ingridient); // initialize ingridients list with mozarella

    if(name == "Chicken Pizza")      // First we fill the ingridients list fully according to the pizza type.
    {
        StringNode* chicken_ingridient = new StringNode("chicken");
        StringNode* corn_ingridient = new StringNode("corn");
        StringNode* mushroom_ingridient = new StringNode("mushroom");
        StringNode* onion_ingridient = new StringNode("onion");
        StringNode* tomato_ingridient = new StringNode("tomato");

        ingridients_list ->add(chicken_ingridient);
        ingridients_list ->add(corn_ingridient);
        ingridients_list ->add(mushroom_ingridient);
        ingridients_list ->add(onion_ingridient);
        ingridients_list ->add(tomato_ingridient);
    }
    if(name == "Broccoli Pizza")
    {
        StringNode* broccoli_ingridient = new StringNode("broccoli");
        StringNode* pepperoni_ingridient = new StringNode("pepperoni");
        StringNode* olive_ingridient = new StringNode("olive");
        StringNode* corn_ingridient = new StringNode("corn");     
        StringNode* onion_ingridient = new StringNode("onion");

        ingridients_list -> add(broccoli_ingridient);        
        ingridients_list -> add(pepperoni_ingridient);
        ingridients_list -> add(olive_ingridient);
        ingridients_list -> add(corn_ingridient);
        ingridients_list -> add(onion_ingridient);
    }
    if(name == "Sausage Pizza")
    {
        StringNode* sausage_ingridient = new StringNode("sausage");
        StringNode* tomato_ingridient = new StringNode("tomato");
        StringNode* olive_ingridient = new StringNode("olive");
        StringNode* mushroom_ingridient = new StringNode("mushroom");                      
        StringNode* corn_ingridient = new StringNode("corn");

        ingridients_list -> add(sausage_ingridient);
        ingridients_list -> add(tomato_ingridient);
        ingridients_list -> add(olive_ingridient);
        ingridients_list -> add(mushroom_ingridient);
        ingridients_list -> add(corn_ingridient);    
    }

    int indices_to_remove[MAX_INGRIDIENT_AMOUNT] = {-1, -1, -1, -1, -1, -1}; // initialize with -1
    int counter = 0;                                                         // sinse there are 6 ingridients maximum of 6 ingridents can be removed
    int remove_input;                                                        // we put the ingridents indices that are wanted to be removed in an array
    cin >> remove_input;
    while(remove_input != 0 )
    {
        indices_to_remove[counter] = remove_input;
        counter++;
        cin >> remove_input;
    }
    counter = 0; // reset the counter
    while(indices_to_remove[counter] != -1) // when we hit -1 there are no more indices to remove
    {
        ingridients_list -> remove_str(indices_to_remove[counter]); // iterate through the array and remove the ingridients with the indeces to be removed
        counter++;
    }

}

Pizza::~Pizza()
{
    delete ingridients_list;
    ingridients_list = NULL;
}

LinkedList* Pizza::get_ingridients_list()
{
    return ingridients_list;
}

void Pizza::print_ingridients() const
{
    StringNode *iter = ingridients_list-> get_string_node_head();
    while(iter)
    {
        cout << iter -> number<< "." <<iter -> data<< endl;
        iter = iter -> next;
    }
}

Order::Order(string in_customer_name, Pizza* first_pizza, Drinks* first_drink)
{
    customer_name = in_customer_name;
    pizzas_list = new LinkedList(first_pizza);
    drinks_list = new LinkedList(first_drink);
}

Order::Order(string in_customer_name, Pizza* first_pizza)
{
    customer_name = in_customer_name;
    Drinks* temp_drink = new Drinks("temp", 1);

    pizzas_list = new LinkedList(first_pizza);  
    drinks_list = new LinkedList(temp_drink);   
    drinks_list -> set_drinks_head(NULL);         
    delete temp_drink;                          
}

Order::~Order()
{
    delete pizzas_list; // pizzas and drinks list destructors are called
    delete drinks_list;
    pizzas_list = NULL;
    drinks_list = NULL;
}

float Order::get_price()
{
    float total = 0;
    int pizza_counter = 0;
    Pizza* pizza_iter = pizzas_list->get_pizza_head();
    string pizza_size = pizza_iter->get_size(); // since all pizzas in one order have to be same size.
    
    while(pizza_iter)
    {
        pizza_counter++;
        pizza_iter = pizza_iter -> next;
    }
    if(pizza_size == "big")
    {
        total += pizza_counter * 25; //25 is the large pizza price
    }
    else if(pizza_size == "medium")
    {
        total += pizza_counter * 20;
    }
    else if(pizza_size == "small")
    {
        total += pizza_counter * 15;
    }   // we are done with pizza prices now moving to drink prices

    Drinks* drink_iter = drinks_list->get_drinks_head();
    while(drink_iter) // if there are no drinks then this step is skipped completely
    {
        if(drink_iter->drink_name == "cola")
            total += drink_iter->amount * 4;
        if(drink_iter->drink_name == "soda")
            total += drink_iter->amount * 2;
        if(drink_iter->drink_name == "ice tea")
            total += drink_iter->amount * 3;
        if(drink_iter->drink_name == "fruit juice")
            total += drink_iter->amount * 3.5;

        drink_iter = drink_iter->next;
    }
    return total;
}

void Order::print_order()
{
    cout << "Name: " << customer_name << endl << endl;

    Pizza* pizza_iter = pizzas_list -> get_pizza_head();
    while(pizza_iter)
    {
        cout << pizza_iter -> get_name() << '(';
        StringNode* ingridient_iter = (pizza_iter -> get_ingridients_list()) -> get_string_node_head();
        while(ingridient_iter)
        {
            cout << ingridient_iter -> data << ", ";
            ingridient_iter = ingridient_iter -> next;
        }
        cout << ')' << endl << "size: " << pizza_iter -> get_size() <<", crust: "<<pizza_iter -> get_crust_type()<< endl << endl;

        pizza_iter = pizza_iter -> next;
    }

    Drinks* drink_iter = drinks_list -> get_drinks_head();
    while(drink_iter)
    {
        cout << drink_iter -> amount <<" " << drink_iter -> drink_name << ", ";
        drink_iter = drink_iter -> next;
    }
    cout <<endl<<"----------------"<<endl;
}

void Order::change_name(string in_name)
{
    customer_name = in_name;
}

OrderList::OrderList()
{
    number_of_orders = 0;
    orders_head = NULL;
}
OrderList::~OrderList()
{
    Order *iter = orders_head, *tail = orders_head;
    while(iter) //iterate through the list, deleting the top most item as we go along
    {
        iter = iter -> next;
        delete tail;
        tail = iter;
    }
}

void OrderList::take_order()
{
    cout << "Pizza Menu" << endl 
    << "1. Chicken Pizza (mozarella, chicken, mushroom, corn, olive, onion, tomato)"<< endl           
    << "2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)" << endl
    << "3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)" << endl
    << "0. Back to main menu" <<endl;

    int pizza_type;
    while(!(cin >> pizza_type)) // not taking string inputs
    {
        cout << "Please enter the pizza number" << endl;
        cin.clear();
        cin.ignore(999, '\n'); //clear 999 chars up untill \n 
    }


    if(pizza_type == 0)
    {
        cout<<endl << "Going back to main menu..." <<endl;
        return;
    }
    string size;
    cout << "Select size: small (15 TL), medium (20 TL), big (25 TL)"<< endl;
    cin >> size;
    string crust_type;
    cout << "Select crust type: thin, normal, thick" << endl;
    cin >> crust_type;

    Pizza* first_pizza = new Pizza(size, crust_type, pizza_type);
    Order* my_order = new Order("place holder name", first_pizza);
    my_order ->next = NULL;                                         //because we take the name last and the implementation i had in mind 
                                                                    //adds the pizzas and drinks one by one, i need to create a order at this stage
                                                                    //to do that i use a placeholder name.
    int pizza_amount;
    cout << "Enter the amount:";
    cin >> pizza_amount;
    if(pizza_amount > 1)
    {
        int counter = 1; // since we created the first pizza, we start from 1.
        while(counter < pizza_amount)
        {
            Pizza* pizza_to_add = new Pizza(*first_pizza);
            my_order ->add_pizza(pizza_to_add);
            counter++;
        }
    }

    cout << "Please choose a drink:" << endl
        <<"0. no drink" << endl
        <<"1. cola 4 TL" << endl
        <<"2. soda 2 TL"<<endl
        <<"3. ice tea 3 TL"<<endl
        <<"4. fruit juice 3.5 TL"<<endl
        <<"Press -1 to save your order"<<endl;

    int choice;
    cin >> choice;
    if(choice != 0) // if no drink wanted, we skip theese steps entirely
    {
        int fruit_juice_counter = 0;
        int cola_counter = 0;
        int soda_counter = 0;
        int ice_tea_counter = 0;
        while(choice != -1) // we count the drink amounts.
        {
            if(choice == 1)
            {
                cola_counter++;
            }
            if(choice == 2)
            {
                soda_counter++;                
            }
            if(choice == 3)
            {
                ice_tea_counter++;
            }
            if(choice == 4)
            {
                fruit_juice_counter++;                
            }
            cin >> choice;
        }
        
        if(cola_counter != 0)   //we create and add drinks to the order.
        {
            Drinks* cola = new Drinks("cola", cola_counter); // drinks created with their string value and amount
            my_order -> add_drink(cola);
        }
        if(soda_counter != 0)
        {
            Drinks* soda = new Drinks("soda", soda_counter);
            my_order -> add_drink(soda);
        }
        if(ice_tea_counter != 0)
        {
            Drinks* ice_tea = new Drinks("ice tea", ice_tea_counter);
            my_order -> add_drink(ice_tea);
        }
        if(fruit_juice_counter != 0)
        {
            Drinks* fruit_juice = new Drinks("fruit juice", fruit_juice_counter);
            my_order -> add_drink(fruit_juice);
        }    
    }

    Order* iter = orders_head; // now adding to the OrderList part
    if(orders_head == NULL)
    {
        orders_head = my_order;
        my_order -> next = NULL;
    }
    while(iter)
    {
        if(iter -> next == NULL)
        {
            iter -> next = my_order;
            my_order -> next = NULL;
        }
        iter = iter->next;
    }

    string name;
    cout << "Please enter your name:" << endl;
    cin >> name;
    my_order ->change_name(name); // change the place holder name to entered name
    my_order -> print_order();
    return;
}

void OrderList::list_orders()
{
    int order_number = 1;
    Order* iter = orders_head;
    while(iter)
    {
        cout<<"----------------"<<endl
            << order_number << endl
            <<"----------------" << endl;
        iter -> print_order();
        iter = iter -> next;
        order_number++;
    }
}

void OrderList::deliver_orders()
{
    list_orders();
    cout<< "Please write the customer name in order to deliver his/her order: ";
    string name;
    cin >> name;
    cout<< endl << "Following order is delivering..." << endl << "-------------"<< endl;

    Order* iter = orders_head;
    Order* tail = iter;
    while(iter)
    {
        if(iter->get_name() == name)
        {
            iter->print_order();
            cout << "Total price: " << iter->get_price() << endl;
            cout << "Do you have a promotion code? (y/n)" << endl;
            char y_n;
            cin >> y_n;
            if(y_n == 'y') // if no promotion code, these steps are skipped
            {
                string promotion_code;
                cout << "Enter promotion code:";

                cin.ignore(999, '\n'); //clear the buffer, \n leftover from cin >> name. i clear 999 chars up until \n just to be safe
                getline(cin, promotion_code);
                if(promotion_code == "I am a student")
                {
                    float new_price = (iter -> get_price()) * 0.9;
                    cout << endl << "New price: "<< new_price << endl;
                }
                else
                {
                    cout << "Promotion code invalid, Price: " << iter -> get_price() << endl; // i didn't know what to do if promotion code was wrong (deliver the order or exit the function?) so i delivered but kept the price same
                }
            }
            
            if(orders_head -> get_name() == name)
            {
                orders_head = orders_head -> next;        
            }

            tail -> next = iter -> next;
            delete iter;
            iter = NULL;
            cout << "The order is delivered successfully!" << endl;
            return;  
        }
        tail = iter;
        iter = iter -> next;
    }
    
    cout << "Order not found" << endl;
    return;

}

int main()
{
    cout << "Welcome to Unicorn Pizza" << endl;
    OrderList my_order_list;

    int choice = 0;

    while(true)
    {
        cout<<"1. Add an order" << endl
            <<"2. List orders"<<endl
            <<"3. Deliver order"<<endl
            <<"4. Exit"<<endl;
        
        while(!(cin >> choice)) // not taking string inputs
        {
            cout << "Please enter a valid choice" << endl;
            cin.clear();
            cin.ignore(999, '\n'); //clear 999 chars up untill \n 
        }


        if(choice == 1)
        {
            my_order_list.take_order();
        }
        else if(choice == 2)
        {
            my_order_list.list_orders();
        }
        else if(choice == 3)
        {
            my_order_list.deliver_orders();
        }
        else if(choice == 4)
        {
            cout << "Goodbye...";
            return 0;
        }
        else
        {
            cout << "Please enter a vaild choice" << endl;
        }
        
    }
}