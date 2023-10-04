#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>

using namespace std;

class Commodity;
class Store;
class InputHandler;


class InputHandler {
public:
    /*
     * The function is used to read a full line into a string variable.
     * It read the redundant '\n' character to prevent the problem of getline function.
     * There is an overload version which can read from the specified data stream.
     * INPUT: None, or fstream
     * RETURN: Full line input by user
     * */
    static string readWholeLine() {
        string input;
        cin.get();
        getline(cin, input);
        return input;
    }

    static string readWholeLine(fstream& file) {
        string input;
        file.get();
        getline(file, input);
        return input;
    }

    /*
     * This function is used to configure whether the input string is a number
     * INPUT: A string
     * RETURN: Bool. True if input string is a number, otherwise false.
     */
    static bool isNum(string& str) {
        for (int i = 0; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    /*
     * Check the input string is a valid number.
     * First check the input is a number or not, then identify whether it is bigger than 0
     * INPUT: string
     * RETURN: bool
     */
    static bool isValidNum(string& str) {
        if (!isNum(str) || (isNum(str) && stoi(str) <= 0))
            return false;
        return true;
    }

    /*
     * Get a number from the user. This function will check the input validation.
     * INPUT: none
     * OUTPUT: integer, the input number
     */
    static int numberInput() {
        string input;
        cin >> input;
        while (!isValidNum(input)) {
            cout << "Please input again your input is NOT an integer or is lower than or equal to 0:" << endl;
            cin >> input;
        }
        return stoi(input);
    }

    /*
     * This function is used in function getInput. Check the input range is inside the specified range
     */
    static int inputCheck(string input, int maxChoiceLen, bool noZero) {
        // Change input to the general integer
        int choice = 0;
        for (int i = 0; i < input.size(); i++) {
            if (isdigit(input[i])) {
                choice = choice * 10 + (input[i] - '0');
            } else {
                return -1;
            }
        }

        if (noZero) {
            return (choice <= maxChoiceLen && choice > 0) ? choice : -1;
        } else {
            return (choice <= maxChoiceLen && choice >= 0) ? choice : -1;
        }
    }

    /*
     * Get the input from the user, and limit the input between the range [0, maxChoiceLen].
     * If noZero is signaled. Then the range will be [1, maxChoiceLen]
     * INPUT: integer, bool(option)
     * OUTPUT: integer, the choice number
     */
    static int getInput(int maxChoiceLen, bool noZero = false) {
        string input;

        cin >> input;
        int choice = inputCheck(input, maxChoiceLen, noZero);
        while (choice == -1) {
            cout << "your input is wrong, please input again:" << endl;
            cin >> input;
            choice = inputCheck(input, maxChoiceLen, noZero);
        }

        return choice;
    }
};

/*
 * Commodity is about an item which the user can buy and the manager can add or delete.
 * ATTRIBUTE:
 *  price: The price of the commodity, an integer.
 *  description: The text which describe the commodity detail, a string.
 *  commodityName: The name of the commodity, a string.
 */
class Commodity {
    protected:
        int price;
        string description;
        string commodityName;

    public:
        ~Commodity() = default;
        Commodity() {
            price = 0;
            description = "";
            commodityName = "";
        }

        Commodity(int price, string commodityName,
                  string description) {
            this->price = price;
            this->commodityName = commodityName;
            this->description = description;
        }

        /*
        * This method will show the full information of the commodity to user interface.
        * There is a overloading version, with an argument amount which will output the information with the amount
        * INPUT: None, or an integer specify the amount of this commodity
        * RETURN: None
        */
        virtual void detail() {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "----------------------------" << endl;
        }

        virtual void detail(int amount) {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "x " << amount << endl;
            cout << "----------------------------" << endl;
        }

        /*
        * Use this function to get the information data from the user, this will init the object.
        * INPUT: none
        * OUTPUT: none
        */
        virtual void userSpecifiedCommodity() {
            cout << "Please input the commodity name:" << endl;
            commodityName = InputHandler::readWholeLine();
            cout << "Please input the commodity price:" << endl;
            price = InputHandler::numberInput();
            cout << "Please input the detail of the commodity:" << endl;
            description = InputHandler::readWholeLine();
        }

        /*
        * Save and load function is used to write the data to the file or read the data from the file.
        * According to the input parameter fstream, they complete the I/O on the specified file.
        * There have no definition of those method, because it is used to be override in the derived class.
        * INPUT: fstream
        * OUTPUT: none
        */
        virtual void save(fstream& file) {}

        virtual void load(fstream& file) {}

        /*
        * The getter function of commodityName
        */
        string getName() {
            return commodityName;
        }

        /*
        * The getter function of price
        */
        int getPrice() {
            return price;
        }

        virtual void inc() {}
        virtual int getA() {}
        virtual int order() {}

};


// cat: iphone12 tea btearphone
class iphone12 : public Commodity {
    private:
        string type;
        string color;
        int gb;
        int am = 1;

    public:
        ~iphone12() = default;
        iphone12() : Commodity{} {
            type = "";
            color = "";
            gb = 0;
        }

        iphone12(string type, string color, int gb, int price, string commodityName, string description) : Commodity{price, commodityName, description} {
            this->type = type;
            this->color = color;
            this->gb = gb;
        }

        void detail() {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "type: " << type << endl;
            cout << "color: " << color << endl;
            cout << "gb: " << gb << endl;
            cout << "----------------------------" << endl;
        }

        void detail(int amount) {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "type: " << type << endl;
            cout << "color: " << color << endl;
            cout << "gb: " << gb << endl;
            cout << "x " << amount << endl;
            cout << "----------------------------" << endl;
        }

        void userSpecifiedCommodity() {
            cout << "Please input the commodity name:" << endl;
            commodityName = InputHandler::readWholeLine();
            cout << "Please input the commodity price:" << endl;
            price = InputHandler::numberInput();
            cout << "Please input the detail of the commodity:" << endl;
            description = InputHandler::readWholeLine();
        }

        void inc() {
            ++am;
        }

        int getA() {
            return am;
        }

        int order() {
            return 0;
        }

        void save(fstream& file) {
            file << order() << endl;
            file << type << endl;
            file << color << endl;
            file << gb << endl;
            file << price << endl;
            file << commodityName << endl;
            file << description << endl;
        }

        void load(fstream& file) {}

};

class tea : public Commodity {
    private:
        string type;
        string size;
        bool ice;
        int am = 1;

    public:
        ~tea() = default;
        tea() : Commodity{} {
            type = "";
            size = "";
            ice = 0;
        }

        tea(string type, string size,
            bool ice, int price, string commodityName,
            string description) : Commodity{price,
            commodityName, description} {
            this->type = type;
            this->size = size;
            this->ice = ice;
        }

        void detail() {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "type: " << type << endl;
            cout << "size: " << size << endl;
            cout << "ice: " << ice << endl;
            cout << "----------------------------" << endl;
        }

        void detail(int amount) {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "type: " << type << endl;
            cout << "size: " << size << endl;
            cout << "ice: " << ice << endl;
            cout << "x " << amount << endl;
            cout << "----------------------------" << endl;
        }

        void userSpecifiedCommodity() {
            cout << "Please input the commodity name:" << endl;
            commodityName = InputHandler::readWholeLine();
            cout << "Please input the commodity price:" << endl;
            price = InputHandler::numberInput();
            cout << "Please input the detail of the commodity:" << endl;
            description = InputHandler::readWholeLine();
        }

        void inc() {
            ++am;
        }

        int getA() {
            return am;
        }

        int order() {
            return 1;
        }

        void save(fstream& file) {
            file << order() << endl;
            file << type << endl;
            file << size << endl;
            file << ice << endl;
            file << price << endl;
            file << commodityName << endl;
            file << description << endl;
        }

        void load(fstream& file) {}
        
};

class btearphone : public Commodity {
    private:
        string type;
        string brand;
        int btv;
        int am = 1;

    public:
        ~btearphone() = default;
        btearphone() : Commodity{} {
            type = "";
            brand = "";
            btv = 0;
        }

        btearphone(string type, string brand, int btv, int price, string commodityName, string description) : Commodity{price, commodityName, description} {
            this->type = type;
            this->brand = brand;
            this->btv = btv;
        }

        void detail() {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "type: " << type << endl;
            cout << "brand: " << brand << endl;
            cout << "btv: " << btv << endl;
            cout << "----------------------------" << endl;
        }
        
        void detail(int amount) {
            cout << commodityName << endl;
            cout << "price: " << price << endl;
            cout << "description: " << description << endl;
            cout << "type: " << type << endl;
            cout << "brand: " << brand << endl;
            cout << "btv: " << btv << endl;
            cout << "x " << amount << endl;
            cout << "----------------------------" << endl;
        }

        void userSpecifiedCommodity() {
            cout << "Please input the commodity name:" << endl;
            commodityName = InputHandler::readWholeLine();
            cout << "Please input the commodity price:" << endl;
            price = InputHandler::numberInput();
            cout << "Please input the detail of the commodity:" << endl;
            description = InputHandler::readWholeLine();
        }

        void inc() {
            ++am;
        }

        int getA() {
            return am;
        }

        int order() {
            return 2;
        }

        void save(fstream& file) {
            file << order() << endl;
            file << type << endl;
            file << brand << endl;
            file << btv << endl;
            file << price << endl;
            file << commodityName << endl;
            file << description << endl;
        }

        void load(fstream& file) {}

};

/*
 * a list storing the existing commodity in the store.
 * There are some method which can modify the content.
 */

bool compare(Commodity* a, Commodity* b) {
    return a->order() < b->order();
}

class CommodityList {
    private:
        vector<Commodity*> list;
        

    public:
        CommodityList() {
            string p[6];
            string order;
            Commodity* newC;

            fstream file;
            file.open("clist.txt", ios::in);

            while(getline(file, order)) {
                if (order == "0") {
                    for (int i = 0; i < 6; ++i) {
                        getline(file, p[i]);
                    }
                    newC = new iphone12(p[0], p[1], stoi(p[2]), stoi(p[3]), p[4], p[5]);
                    list.push_back(newC);
                } else if (order == "1") {
                    for (int i = 0; i < 6; ++i) {
                        getline(file, p[i]);
                    }
                    newC = new tea(p[0], p[1], stoi(p[2]), stoi(p[3]), p[4], p[5]);
                    list.push_back(newC);
                } else {
                    for (int i = 0; i < 6; ++i) {
                        getline(file, p[i]);
                    }
                    newC = new btearphone(p[0], p[1], stoi(p[2]), stoi(p[3]), p[4], p[5]);
                    list.push_back(newC);
                }
            }

            file.close();
        }

        /*
        * Print the full information of the commodities inside the list
        * You must call Commodity.detail() to show the commodity information.
        * INPUT: None
        * RETURN: None
        */
        void showCommoditiesDetail() {
            bool p = 0, t = 0, b = 0;
            for (int i = 0; i < list.size(); ++i) {
                if (list[i]->order() == 0 && !p) {
                    cout << "iphone12: " << endl;
                    p = 1;
                } else if (list[i]->order() == 1 && !t) {
                    cout << "tea: " << endl;
                    t = 1;
                } else if (list[i]->order() == 2 && !b) {
                    cout << "btearphone: " << endl;
                    b = 1;
                } else {

                }

                cout << (i + 1) << ". ";
                list[i]->detail();
            }
        }

        /*
        * Print only the commodity name of the commodities inside the list
        * You don't need to use Commodity.detail() here, just call the Commodity.getName() function
        * INPUT: None
        * RETURN: None
        */
        void showCommoditiesName() {
            bool p = 0, t = 0, b = 0;
            for (int i = 0; i < list.size(); ++i) {
                if (list[i]->order() == 0 && !p) {
                    cout << "iphone12: " << endl;
                    p = 1;
                } else if (list[i]->order() == 1 && !t) {
                    cout << "tea: " << endl;
                    t = 1;
                } else if (list[i]->order() == 2 && !b) {
                    cout << "btearphone: " << endl;
                    b = 1;
                } else {

                }

                cout << (i + 1) << ". ";
                cout << list[i]->getName() << endl;
            }
        }

        /*
        * Check whether the list is empty or not
        * INPUT: None
        * RETURN: Bool. True if the list is empty, otherwise false
        */
        bool empty() {
            return list.empty();
        }

        /*
        * Return the size(or length) of the list
        * INPUT: None
        * RETURN: Integer. List size
        */
        int size() {
            return list.size();
        }

        /*
        * Return a commodity object at specified position
        * INPUT: Integer. The index of that commodity
        * RETURN: Commodity. The wanted commodity object
        */
        Commodity* get(int index) {
            return list[index];
        }

        /*
        * Push a new commodity object into the list
        * INPUT: Commodity. The object need to be pushed
        * RETURN: None
        */
        void add(Commodity* newCommodity, string& cat) { // cat: iphone12 tea btearphone
            list.push_back(newCommodity);
            sort(list.begin(), list.end(), compare);
        }

        /*
        * Check the input commodity object is existing inside the list
        * If the commodity name is the same, we take those objects the same object
        * INPUT: Commodity. The object need to be checked
        * OUTPUT: Bool. True if the object existing, otherwise false
        */
        bool isExist(Commodity* commodity) {
            string n = commodity->getName();
            for (int i = 0; i < list.size(); ++i) {
                if (n == list[i]->getName()) {
                    return 1;
                }
            }
            return 0;
        }

        /*
        * Remove an object specified by the position
        * INPUT: Integer. The position of the object which need to be removed
        * OUTPUT: None
        */
        void remove(int index) {
            list.erase(list.begin() + index);
        }

        void save() {
            fstream file;
            file.open("clist.txt", ios::out | ios::trunc);

            for (int i = 0; i < list.size(); ++i) {
                list[i]->save(file);
            }

            file.close();
        }
};

/*
 * is used to store the commodities user wanted.
 * Because the same name represents the same object, if there is a commodity which have more than one object inside
 * the cart, then it will be store as the same object and the cart must keep the amount of the object.
 */
class ShoppingCart {
    private:
        vector<Commodity*> items;

    public:

        /*
        * Push an commodity object into the cart.
        * Be careful that if the input object is existing in the list, then keep the amount of that object rather than
        * actually push the object into the cart.
        * INPUT: Commodity. The object need to be pushed.
        * OUTPUT: None.
        */
        void push(Commodity* entry) {
            bool ex = 0;
            string n = entry->getName();
            for(int i = 0; i < items.size(); ++i){
                if(n == items[i]->getName()) {
                    items[i]->inc();
                    ex = 1;
                }
            }
            if (ex == 0)
                items.push_back(entry);
        }

        /*
        * Show the content of the cart to user interface.
        * INPUT: None.
        * OUTPUT: None.
        */
        void showCart() {
            int a = 0;
            for (int i = 0; i < items.size(); ++i) {
                cout << (i + 1) << ". " << endl;
                items[i]->detail(items[i]->getA());
                a += items[i]->getA();
            }
            cout << "tot: " << a << endl;
        }

        /*
        * Return the cart size. (The same object must be seen as one entry)
        * INPUT: None.
        * OUTPUT: Integer. The cart size.
        */
        int size() {
            return items.size();
        }

        /*
        * Remove an entry from the cart. Don't care about the amount of the commodity, just remove it.
        * INPUT: The order of the entry.
        * OUTPUT: None.
        */
        void remove(int index) {
            items.erase(items.begin() + index);
        }

        /*
        * Check the total amount of price for the user.
        * Remember to clear the list after checkout.
        * INPUT: None.
        * OUTPUT: Integer. The total price.
        */
        int checkOut() {
            int tp = 0;
            for (int i = 0; i < items.size(); ++i) {
                tp += (items[i]->getPrice() * items[i]->getA());
            }
            items.clear();

            return tp;
        }

        /*
        * Check if the cart have nothing inside.
        * INPUT: None.
        * OUTPUT: Bool. True if the cart is empty, otherwise false.
        */
        bool empty() {
            return items.empty();
        }
};

/*
 * SUPER DIFFICULT>_<
 * The Store class manage the flow of control, and the interface showing to the user.
 * Store use status to choose the interface to show. As the result, status control is very important here.
 * The detail of Store is in the README
 */
class Store {
private:
    enum UMode {USER, MANAGER} userStatus;
    enum SMode {OPENING, DECIDING, SHOPPING, CART_CHECKING, CHECK_OUT, MANAGING, CLOSE} storeStatus;
    CommodityList commodityList;
    ShoppingCart cart;


    void commodityInput() {
        string name, detail, s1, s2, price, b, n1;
        string ctype;
        Commodity* newC;

        cout << "WT ?" << endl;
        cin >> ctype;
        cin.get();
        if (ctype == "iphone12") {
            cout << "name:" << endl;
            getline(cin, name);
            cout << "price:" << endl;
            getline(cin, price);
            cout << "detail:" << endl;
            getline(cin, detail);

            cout << "type:" << endl;
            getline(cin, s1);
            cout << "color:" << endl;
            getline(cin, s2);
            cout << "gb:" << endl;
            getline(cin, n1);

            newC = new iphone12(s1, s2, stoi(n1), stoi(price), name, detail);

            if (commodityList.isExist(newC)) {
                cout << "[WARNING] " << name << " is exist in the store. If you want to edit it, please delete it first" << endl;
            } else {
                commodityList.add(newC, ctype);
            }
        } else if (ctype == "tea") {
            cout << "name:" << endl;
            getline(cin, name);
            cout << "price:" << endl;
            getline(cin, price);
            cout << "detail:" << endl;
            getline(cin, detail);

            cout << "type:" << endl;
            getline(cin, s1);
            cout << "size:" << endl;
            getline(cin, s2);
            cout << "ice(0 or 1):" << endl;
            getline(cin, b);

            newC = new tea(s1, s2, stoi(b), stoi(price), name, detail);

            if (commodityList.isExist(newC)) {
                cout << "[WARNING] " << name << " is exist in the store. If you want to edit it, please delete it first" << endl;
            } else {
                commodityList.add(newC, ctype);
            }
        } else if (ctype == "btearphone") {
            cout << "name:" << endl;
            getline(cin, name);
            cout << "price:" << endl;
            getline(cin, price);
            cout << "detail:" << endl;
            getline(cin, detail);

            cout << "type:" << endl;
            getline(cin, s1);
            cout << "brand:" << endl;
            getline(cin, s2);
            cout << "btv:" << endl;
            getline(cin, n1);

            newC = new btearphone(s1, s2, stoi(n1), stoi(price), name, detail);

            if (commodityList.isExist(newC)) {
                cout << "[WARNING] " << name << " is exist in the store. If you want to edit it, please delete it first" << endl;
            } else {
                commodityList.add(newC, ctype);
            }
        } else {
            cout << "error!" << endl;
        }
    }

    void deleteCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        int choice;
        cout << "There are existing commodity in our store:" << endl;
        commodityList.showCommoditiesName();
        cout << "Or type 0 to regret" << endl
             << "Which one do you want to delete?" << endl;

        choice = InputHandler::getInput(commodityList.size());

        if (choice != 0) {
            commodityList.remove(choice - 1);
        }
    }

    void showCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        cout << "Here are all commodity in our store:" << endl;
        commodityList.showCommoditiesDetail();
        cout << endl;
    }

    void askMode() {
        string input;

        cout << "Are you a general user or a manager?" << endl
             << "1. general user, 2. manager" << endl
             << "Or type 0 to close the store" << endl;

        int choice = InputHandler::getInput(2);

        userStatus = (choice == 2) ? UMode::MANAGER : UMode::USER;

        if (choice == 0) {
            storeStatus = SMode::CLOSE;
        } else if (userStatus == UMode::USER) {
            storeStatus = SMode::DECIDING;
        } else if (userStatus == UMode::MANAGER) {
            storeStatus = SMode::MANAGING;
        }
    }

    void decideService() {
        string input;

        cout << "Below are our service:" << endl
             << "1. Buy the commodity you want" << endl
             << "2. Check your shopping cart" << endl
             << "3. Check out" << endl
             << "Or type 0 to exit user mode" << endl
             << "You may choose what you need:" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            storeStatus = SMode::SHOPPING;
        } else if (choice == 2) {
            storeStatus = SMode::CART_CHECKING;
        } else if (choice == 3) {
            storeStatus = SMode::CHECK_OUT;
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void chooseCommodity() {
        string input;
        showCommodity();
        cout << "Or input 0 to exit shopping" << endl;

        int choice = InputHandler::getInput(commodityList.size());

        // Push the commodity into shopping cart here
        if (choice == 0) {
            storeStatus = SMode::DECIDING;
        } else {
            // May be some bug here, test later
            cart.push(commodityList.get(choice - 1));
        }
    }

    void showCart() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty" << endl;
            storeStatus = SMode::DECIDING;
            return;
        }

        int choice;
        do {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();

            cout << "Do you want to delete the entry from the cart?" << endl
                 << "1. yes, 2. no" << endl;

            choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                cout << "Which one do you want to delete(type the commodity index)?" << endl
                     << "Or type 0 to regret" << endl;
                int index = InputHandler::getInput(cart.size());
                // **
                if (index == 0) {
                    break;
                }
                cart.remove(index - 1);
            }
        } while (choice == 1);

        cout << "Do you want to checkout?" << endl
             << "1. yes, 2. No, I want to buy more" << endl;
        choice = InputHandler::getInput(2, true);
        if (choice == 1) {
            storeStatus = SMode::CHECK_OUT;
        } else {
            storeStatus = SMode::DECIDING;
        }
    }

    void checkOut() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty, nothing can checkout" << endl;
        } else {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();
            cout << "Are you sure you want to buy all of them?" << endl
                 << "1. Yes, sure, 2. No, I want to buy more" << endl;

            int choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                int amount = cart.checkOut();
                cout << "Total Amount: " << amount << endl;
                cout << "Thank you for your coming!" << endl;
                cout << "------------------------------" << endl << endl;
            }
        }

        storeStatus = SMode::DECIDING;
    }

    void managerInterface() {
        cout << "Here are some manager services you can use:" << endl
             << "1. Add new commodity" << endl
             << "2. Delete commodity from the commodity list" << endl
             << "3. Show all existing commodity" << endl
             << "Or type 0 to exit manager mode" << endl
             << "Which action do you need?" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            commodityInput();
        } else if (choice == 2) {
            deleteCommodity();
        } else if (choice == 3) {
            showCommodity();
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void userInterface() {
        if (storeStatus == SMode::OPENING) {
            askMode();
        } else if (storeStatus == SMode::DECIDING) {
            decideService();
        } else if (storeStatus == SMode::SHOPPING) {
            chooseCommodity();
        } else if (storeStatus == SMode::CART_CHECKING) {
            showCart();
        } else if (storeStatus == SMode::CHECK_OUT) {
            checkOut();
        } else if (storeStatus == SMode::MANAGING) {
            managerInterface();
        } else if (storeStatus == SMode::CLOSE) {
            return;
        }
    }

public:
    Store() {
        userStatus = UMode::USER;
        storeStatus = SMode::CLOSE;
    }

    void open() {
        storeStatus = SMode::OPENING;
        while (storeStatus != SMode::CLOSE) {
            userInterface();
        }
        commodityList.save();
    }
};


int main() {
    Store csStore;
    csStore.open();
    return 0;
}
