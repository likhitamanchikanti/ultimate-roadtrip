#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <chrono>
#include <stack>
#include <sstream>

using namespace std;

class Node
{
public:
    float latitude;
    float longitude;
    string address;
    Node* left = nullptr;
    Node* right = nullptr;
};

class Tree
{
public:
    Node* root = nullptr;
    Node* insert(Node* node, float key, Node* tempNode);

};


Node* Tree::insert(Node* node, float key, Node* tempNode)
{
    if (node == nullptr)
        node = tempNode;

    else if (node->latitude > key)
        node->left = insert(node->left, key, tempNode);

    else if (node->latitude < key)
        node->right = insert(node->right, key, tempNode);

    return node;
}


void loadSubway(map<float, pair<float, string>> &m, Tree* tree){

    ifstream file("data/Subway_US.csv");
    string lineFromFile;

    while(!file.eof()){

        Node* tempNode = new Node();

        getline(file, lineFromFile, ',' );

        if(lineFromFile.empty()){
            break;
        }

        float longitude = stof(lineFromFile);
        tempNode->longitude = longitude;

        getline(file, lineFromFile, ',' );
        float latitude = stof(lineFromFile);
        tempNode->latitude = latitude;

        getline(file, lineFromFile, '|' );
        string temp = lineFromFile;
        string address = temp.substr(1);
        tempNode->address = address;

        tree->root = tree->insert(tree->root, latitude, tempNode);
        m[latitude] = make_pair(longitude, address);

        string throwaway;
        getline(file, throwaway);

    }

}

void loadBP(map<float, pair<float, string>> &m, Tree* tree){

    ifstream file("data/BP Stations_USA.csv");
    string lineFromFile;

    while(!file.eof()){

        Node* tempNode = new Node();

        getline(file, lineFromFile, ',' );

        if(lineFromFile.empty()){
            break;
        }

        float longitude = stof(lineFromFile);
        tempNode->longitude = longitude;

        getline(file, lineFromFile, ',' );
        float latitude = stof(lineFromFile);
        tempNode->latitude = latitude;

        getline(file, lineFromFile, '(');
        string temp = lineFromFile;
        string address = temp.substr(1, temp.length() - 3);
        tempNode->address = address;

        tree->root = tree->insert(tree->root, latitude, tempNode);
        m[latitude] = make_pair(longitude, address);

        string throwaway;
        getline(file, throwaway);

    }

}

void loadsevenEleven(map<float, pair<float, string>> &m, Tree* tree){

    ifstream file("data/Seven Eleven-US.csv");
    string lineFromFile;

    while(!file.eof()){

        Node* tempNode = new Node();

        getline(file, lineFromFile, ',' );

        if(lineFromFile.empty()){
            break;
        }

        float longitude = stof(lineFromFile);
        tempNode->longitude = longitude;

        getline(file, lineFromFile, ',' );
        float latitude = stof(lineFromFile);
        tempNode->latitude = latitude;

        getline(file, lineFromFile, '(');
        string temp = lineFromFile;
        string address = temp.substr(1, temp.length() - 3);
        tempNode->address = address;

        tree->root = tree->insert(tree->root, latitude, tempNode);
        m[latitude] = make_pair(longitude, address);

        string throwaway;
        getline(file, throwaway);

    }

}

void loadchaseBank(map<float, pair<float, string>> &m, Tree* tree){

    ifstream file("data/Chase_Bank_Branches & ATM,s.csv");
    string lineFromFile;

    while(!file.eof()){

        Node* tempNode = new Node();

        getline(file, lineFromFile, ',' );

        if(lineFromFile.empty()){
            break;
        }

        float longitude = stof(lineFromFile);
        tempNode->longitude = longitude;

        getline(file, lineFromFile, ',' );
        float latitude = stof(lineFromFile);
        tempNode->latitude = latitude;

        getline(file, lineFromFile, '|');
        string temp = lineFromFile;

        if (temp.find('-') != string::npos)
            temp = temp.substr(0,temp.length() - 14);

        string address = temp.substr(1, temp.length() - 1);
        tempNode->address = address;

        tree->root = tree->insert(tree->root, latitude, tempNode);
        m[latitude] = make_pair(longitude, address);

        string throwaway;
        getline(file, throwaway);

    }

}

void loadDominoses(map<float, pair<float, string>>& m, Tree* tree)
{
    string line;
    stringstream SS;
    string dummy1, dummy2, dummy3, quote1;
    string latstr, longstr, addressLine1, addressLine2;
    float latitude, longitude;
    string address;
    string city, state, zip;

    string filename = "data/Dominos Pizza.csv";
    ifstream file;

    file.open(filename);

    if (file.is_open())
    {
        while(getline(file, line))
        {
            Node* tempNode = new Node();

            SS.clear();
            SS.str(line);

            getline(SS, longstr, ',');
            longitude = stof(longstr);
            tempNode->longitude = longitude;

            getline(SS, latstr, ',');
            latitude = stof(latstr);
            tempNode->latitude = latitude;

            getline(SS, dummy1, ',');
            getline(SS, dummy2, ',');
            getline(SS, quote1, '"');

            getline(SS, addressLine1, ',');
            getline(SS, dummy3, ' ');
            getline(SS, city, ',');
            getline(SS, state, ' ');
            getline(SS, zip, ',');

            address = addressLine1 + ", ";
            address += city + ", ";
            address += state + " ";
            address += zip;
            tempNode->address = address;

            m[latitude] = {longitude, address};
            tree->root = tree->insert(tree->root, latitude, tempNode);
        }
    }
}

void loadDunkins(map<float, pair<float, string>>& m, Tree* tree)
{
    string line;
    stringstream SS;
    string dummy1, dummy2, quote1;
    string latstr, longstr, addressLine1, addressLine2;
    float latitude, longitude;
    string address;

    string filename = "data/dunkin.csv";
    ifstream file;

    file.open(filename);

    if (file.is_open())
    {
        while(getline(file, line))
        {
            Node* tempNode = new Node();

            SS.clear();
            SS.str(line);

            getline(SS, longstr, ',');
            longitude = stof(longstr);
            tempNode->longitude = longitude;

            getline(SS, latstr, ',');
            latitude = stof(latstr);
            tempNode->latitude = latitude;

            getline(SS, dummy1, ',');
            getline(SS, dummy2, ',');
            getline(SS, quote1, '"');

            getline(SS, addressLine1, '|');
            getline(SS, addressLine2, '|');
            address = addressLine1 + ", ";
            address += addressLine2;
            tempNode->address = address;

            tree->root = tree->insert(tree->root, latitude, tempNode);
            m[latitude] = {longitude, address};
        }
    }
}

void loadPNCBanks(map<float, pair<float, string>>& m, Tree* tree)
{
    string line;
    stringstream SS;
    string dummy1, dummy2, dummy3, quote1;
    string latstr, longstr, addressLine1, addressLine2;
    float latitude, longitude;
    string address;
    string city, state, zip;

    string filename = "data/PNC.csv";
    ifstream file;

    file.open(filename);

    if (file.is_open())
    {
        while(getline(file, line))
        {
            Node* tempNode = new Node();

            SS.clear();
            SS.str(line);

            getline(SS, longstr, ',');
            longitude = stof(longstr);
            tempNode->longitude = longitude;

            getline(SS, latstr, ',');
            latitude = stof(latstr);
            tempNode->latitude = latitude;

            getline(SS, dummy1, '-');
            getline(SS, dummy2, ' ');

            getline(SS, addressLine1, ';');

            getline(SS, dummy3, ' ');
            getline(SS, city, ',');
            getline(SS, state, ' ');
            getline(SS, zip, '>');

            address = addressLine1 + ", ";
            address += city + ", ";
            address += state + " ";
            address += zip;
            tempNode->address = address;

            tree->root = tree->insert(tree->root, latitude, tempNode);
            m[latitude] = {longitude, address};
        }
    }
}

void loadRestAreas(map<float, pair<float, string>>& m, Tree* tree)
{
    string line;
    stringstream SS;
    string latstr, longstr, dummy, quote;
    float latitude, longitude;
    string address;
    string state, highway, bound, name, milemarker;

    string filename = "data/RestAreasCombined_USA.csv";
    ifstream file;

    file.open(filename);

    if (file.is_open())
    {
        while(getline(file, line))
        {
            Node* tempNode = new Node();

            SS.clear();
            SS.str(line);

            getline(SS, longstr, ',');
            longitude = stof(longstr);
            tempNode->longitude = longitude;

            getline(SS, latstr, ',');
            latitude = stof(latstr);
            tempNode->latitude = latitude;

            getline(SS, quote, '"');

            getline(SS, state, ',');
            getline(SS, highway, ',');
            getline(SS, bound, ',');
            getline(SS, name, ',');
            getline(SS, dummy, ' ');
            getline(SS, milemarker, '"');

            address = name + " (in ";
            address += state + ", on ";
            address += highway + " ";
            address += bound + " at ";
            address += milemarker + ")";
            tempNode->address = address;

            tree->root = tree->insert(tree->root, latitude, tempNode);
            m[latitude] = {longitude, address};
        }
    }
}

void loadStarbuckses(map<float, pair<float, string>>& m, Tree* tree)
{
    string line;
    stringstream SS;
    string dummy1, dummy2, quote1;
    string latstr, longstr, addressLine1, addressLine2;
    float latitude, longitude;
    string address;
    string city;
    string state;
    string zip;

    string filename = "data/starbucks.csv";
    ifstream file;

    file.open(filename);

    if (file.is_open())
    {
        while(getline(file, line))
        {
            Node* tempNode = new Node();

            SS.clear();
            SS.str(line);

            getline(SS, longstr, ',');
            longitude = stof(longstr);
            tempNode->longitude = longitude;

            getline(SS, latstr, ',');
            latitude = stof(latstr);
            tempNode->latitude = latitude;

            getline(SS, dummy1, ',');
            getline(SS, quote1, '"');

            getline(SS, addressLine1, ';');
            getline(SS, dummy2, ' ');
            getline(SS, city, ',');
            getline(SS, dummy2, ' ');
            getline(SS, state, ' ');
            getline(SS, zip, '"');

            auto it = zip.begin()+5;
            if (*it == ';')
            {
                zip.erase(zip.begin()+5, zip.end());
            }

            addressLine2 = city + ", ";
            addressLine2 += state + " ";
            addressLine2 += zip;

            address = addressLine1 + ", ";
            address += addressLine2;
            tempNode->address = address;

            tree->root = tree->insert(tree->root, latitude, tempNode);
            m[latitude] = {longitude, address};
        }
    }
}


void loadWendys(map<float, pair<float, string>>& m, Tree* tree){
    ifstream myfile("data/wendys.csv");
    string linefromfile;

    while(!myfile.eof()){

        Node* tempNode = new Node();

        getline(myfile, linefromfile, ',');
        if(linefromfile.empty()){
            break;
        }

        float longitude = stof(linefromfile);
        tempNode->longitude = longitude;


        getline(myfile, linefromfile, ',');
        float latitude = stof(linefromfile);
        tempNode->latitude = latitude;


        getline(myfile, linefromfile, '(');
        string temp = linefromfile;
        string address = temp.substr(1, temp.length() -3);
        tempNode->address = address;

        m[latitude] = make_pair(longitude, address);
        tree->root = tree->insert(tree->root, latitude, tempNode);

        string throwaway;
        getline(myfile, throwaway);

    }
}
void loadburgerKing(map<float, pair<float, string>>& m, Tree* tree){
    ifstream myfile("data/burgerking.csv");
    string linefromfile;

    while(!myfile.eof()){
        Node* tempNode = new Node();

        getline(myfile, linefromfile, ',');
        if(linefromfile.empty()){
            break;
        }

        float longitude = stof(linefromfile);
        tempNode->longitude = longitude;


        getline(myfile, linefromfile, ',');
        float latitude = stof(linefromfile);
        tempNode->latitude = latitude;

        getline(myfile, linefromfile, '(');
        string temp = linefromfile;
        string address = temp.substr(1, temp.length() -3);
        tempNode->address = address;

        m[latitude] = make_pair(longitude, address);
        tree->root = tree->insert(tree->root, latitude, tempNode);

        string throwaway;
        getline(myfile, throwaway);

    }
}
void loadmcDonalds(map<float, pair<float, string>>& m, Tree* tree){
    ifstream myfile("data/mcdonalds.csv");
    string linefromfile;

    while(!myfile.eof()){

        Node* tempNode = new Node();

        getline(myfile, linefromfile, ',');
        if(linefromfile.empty()){
            break;
        }

        float longitude = stof(linefromfile);
        tempNode->longitude = longitude;

        getline(myfile, linefromfile, ',');
        float latitude = stof(linefromfile);
        tempNode->latitude = latitude;

        getline(myfile, linefromfile, '(');
        string temp = linefromfile;
        string address = temp.substr(1, temp.length() -3);
        tempNode->address = address;

        m[latitude] = make_pair(longitude, address);
        tree->root = tree->insert(tree->root, latitude, tempNode);

        string throwaway;
        getline(myfile, throwaway);

    }
}
void loadpizzaHut(map<float, pair<float, string>>& m, Tree* tree){
    ifstream myfile("data/pizzahut.csv");
    string linefromfile;

    while(!myfile.eof()){

        Node* tempNode = new Node();

        getline(myfile, linefromfile, ',');
        if(linefromfile.empty()){
            break;
        }

        float longitude = stof(linefromfile);
        tempNode->longitude = longitude;


        getline(myfile, linefromfile, ',');
        float latitude = stof(linefromfile);
        tempNode->latitude = latitude;


        getline(myfile, linefromfile, '(');
        string temp = linefromfile;
        string address = temp.substr(1, temp.length() -3);
        tempNode->address = address;

        m[latitude] = make_pair(longitude, address);
        tree->root = tree->insert(tree->root, latitude, tempNode);


        string throwaway;
        getline(myfile, throwaway);

    }
}

string findNearestMap(const map<float, pair<float, string>> &m, float latitude, float longitude)
{
    const float indivThreshold = 0.5;
    const float userLatLongSum = abs(latitude) + abs(longitude);

    string closestaddress = m.begin()->second.second;
    float currLatLongSum = abs(m.begin()->first) + abs(m.begin()->second.first);
    float combinedThreshold = abs(currLatLongSum - userLatLongSum);

    for (auto it = m.begin(); it != m.end(); ++it)
    {
        float latdifference = abs(abs(it->first) - abs(latitude));
        float longdifference = abs(abs(it->second.first) - abs(longitude));

        if (latdifference > indivThreshold && longdifference > indivThreshold)
            continue;

        else 	// both lat and long are within 1.0
        {
            float temp = abs(it->first) + abs(it->second.first);

            if (abs(temp - userLatLongSum) < combinedThreshold)
            {
                combinedThreshold = abs(temp - currLatLongSum);
                currLatLongSum = temp;
                closestaddress = it->second.second;
            }

        }
    }

    return closestaddress;
}



void findNearestTree(const float &indivThreshold, const float &userLatLongSum, string &closestaddress, float &currLatLongSum, float &combinedThreshold, Node* root, float latitude, float longitude){

    // code from Aditi's Stepik exercises
    if(root == NULL)
        return;

    if(root != NULL){

        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, root->left, latitude, longitude); //goes to left
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, root->right, latitude, longitude); //goes to right

        float latdifference = abs(abs(root->latitude) - abs(latitude));
        float longdifference = abs(abs(root->longitude) - abs(longitude));

        if (latdifference > indivThreshold && longdifference > indivThreshold){

        }

        else 	// both lat and long are within 1.0
        {
            float temp = abs(root->latitude) + abs(root->longitude);

            if (abs(temp - userLatLongSum) < combinedThreshold)
            {
                combinedThreshold = abs(temp - currLatLongSum);
                currLatLongSum = temp;
                closestaddress = root->address;
            }

        }

    }


}


int main() {

    float latitude, longitude;
    int option;
    string mapAddress;
    string treeAddress;
    map<int, string> places;

    places.insert({1, "Dominos"});
    places.insert({2, "Dunkin Donuts"});
    places.insert({3, "PNC Bank"});
    places.insert({4, "Rest Area"});
    places.insert({5, "Starbucks"});
    places.insert({6, "Subway"});
    places.insert({7, "BP"});
    places.insert({8, "7-Eleven"});
    places.insert({9, "Chase Bank"});
    places.insert({10, "Wendy's"});
    places.insert({11, "Burger King"});
    places.insert({12, "McDonald's"});
    places.insert({13, "Pizza Hut"});

    map<float, pair<float, string>> dominosMap;
    map<float, pair<float, string>> dunkinMap;
    map<float, pair<float, string>> pncMap;
    map<float, pair<float, string>> restareaMap;
    map<float, pair<float, string>> starbucksMap;
    map<float, pair<float, string>> subwayMap;
    map<float, pair<float, string>> bpMap;
    map<float, pair<float, string>> sevenElevenMap;
    map<float, pair<float, string>> chasebankMap;
    map<float, pair<float, string>> wendysMap;
    map<float, pair<float, string>> burgerKingMap;
    map<float, pair<float, string>> mcDonaldsMap;
    map<float, pair<float, string>> pizzaHutMap;

    Tree* dominosTree = new Tree();
    Tree* dunkinTree = new Tree();
    Tree* pncTree = new Tree();
    Tree* restareaTree = new Tree();
    Tree* starbucksTree = new Tree();
    Tree* subwayTree = new Tree();
    Tree* bpTree = new Tree();
    Tree* sevenElevenTree = new Tree();
    Tree* chasebankTree = new Tree();
    Tree* wendysTree= new Tree();
    Tree* burgerKingTree= new Tree();
    Tree* mcDonaldsTree= new Tree();
    Tree* pizzaHutTree= new Tree();

    cout << "Welcome to the" << endl;
    cout << "╔===============================╗" << endl;
    cout << "╟ The Ultimate Road Trip Guide! ╢" << endl;
    cout << "╚===============================╝" << endl;
    cout << "Please enter your coordinates." << endl;
    cout << "Latitude: ";
    cin >> latitude;
    cout << "Longitude: ";
    cin >> longitude;

    cout << "\nWhere are you headed?" << endl;
    cout << "1. Dominos" << endl;
    cout << "2. Dunkin Donuts" << endl;
    cout << "3. PNC Bank" << endl;
    cout << "4. Rest Areas" << endl;
    cout << "5. Starbucks" << endl;
    cout << "6. Subway" << endl;
    cout << "7. BP" << endl;
    cout << "8. 7-Eleven" << endl;
    cout << "9. ChaseBank" << endl;
    cout << "10. Wendy\'s" << endl;
    cout << "11. Burger King" << endl;
    cout << "12. McDonald\'s" << endl;
    cout << "13. Pizza Hut" << endl;

    cin >> option;

    cout << "\nFinding nearest " << places.at(option) << "..." << endl;

    //code for timing functions taken from https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/
    auto start1 = chrono::steady_clock::now();
    auto end1 = chrono::steady_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>( end1 - start1 ).count();
    auto start2 = chrono::steady_clock::now();
    auto end2 = chrono::steady_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>( end2 - start2 ).count();

    const float indivThreshold = 0.5;
    const float userLatLongSum = abs(latitude) + abs(longitude);

    if (option == 1){
        loadDominoses(dominosMap, dominosTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(dominosMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = dominosTree->root->address;
        float currLatLongSum = abs(dominosTree->root->latitude) + abs(dominosTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, dominosTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 2){
        loadDunkins(dunkinMap, dunkinTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(dunkinMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = dunkinTree->root->address;
        float currLatLongSum = abs(dunkinTree->root->latitude) + abs(dunkinTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, dunkinTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 3){
        loadPNCBanks(pncMap, pncTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(pncMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = pncTree->root->address;
        float currLatLongSum = abs(pncTree->root->latitude) + abs(pncTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, pncTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 4){
        loadRestAreas(restareaMap, restareaTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(restareaMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = restareaTree->root->address;
        float currLatLongSum = abs(restareaTree->root->latitude) + abs(restareaTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, restareaTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 5){
        loadStarbuckses(starbucksMap, starbucksTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(starbucksMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = starbucksTree->root->address;
        float currLatLongSum = abs(starbucksTree->root->latitude) + abs(starbucksTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, starbucksTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 6){
        loadSubway(subwayMap, subwayTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(subwayMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = subwayTree->root->address;
        float currLatLongSum = abs(subwayTree->root->latitude) + abs(subwayTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, subwayTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 7){
        loadBP(bpMap, bpTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(bpMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = bpTree->root->address;
        float currLatLongSum = abs(bpTree->root->latitude) + abs(bpTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, bpTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 8){
        loadsevenEleven(sevenElevenMap, sevenElevenTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(sevenElevenMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = sevenElevenTree->root->address;
        float currLatLongSum = abs(sevenElevenTree->root->latitude) + abs(sevenElevenTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, sevenElevenTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 9){
        loadchaseBank(chasebankMap, chasebankTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(chasebankMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = chasebankTree->root->address;
        float currLatLongSum = abs(chasebankTree->root->latitude) + abs(chasebankTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, chasebankTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 10 ){
        loadWendys(wendysMap, wendysTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(wendysMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = wendysTree->root->address;
        float currLatLongSum = abs(wendysTree->root->latitude) + abs(wendysTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, wendysTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 11){
        loadburgerKing(burgerKingMap, burgerKingTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(burgerKingMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = burgerKingTree->root->address;
        float currLatLongSum = abs(burgerKingTree->root->latitude) + abs(burgerKingTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, burgerKingTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    else if (option == 12){
        loadmcDonalds(mcDonaldsMap, mcDonaldsTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(mcDonaldsMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = mcDonaldsTree->root->address;
        float currLatLongSum = abs(mcDonaldsTree->root->latitude) + abs(mcDonaldsTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, mcDonaldsTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();

    }

    else if (option == 13){
        loadpizzaHut(pizzaHutMap, pizzaHutTree);

        start1 = chrono::steady_clock::now();
        mapAddress = findNearestMap(pizzaHutMap, latitude, longitude);
        end1 = chrono::steady_clock::now();
        duration1 = chrono::duration_cast<chrono::microseconds>( end1 - start1 ).count();

        string closestaddress = pizzaHutTree->root->address;
        float currLatLongSum = abs(pizzaHutTree->root->latitude) + abs(pizzaHutTree->root->longitude);
        float combinedThreshold = abs(currLatLongSum - userLatLongSum);

        start2 = chrono::steady_clock::now();
        findNearestTree(indivThreshold, userLatLongSum, closestaddress, currLatLongSum, combinedThreshold, pizzaHutTree->root, latitude, longitude);
        treeAddress = closestaddress;
        end2 = chrono::steady_clock::now();
        duration2 = chrono::duration_cast<chrono::microseconds>( end2 - start2 ).count();
    }

    cout << "\nThe nearest " << places.at(option) << " is located at: " << endl;
    cout << mapAddress << " (result from map data structure, " << duration1 << " microseconds)" << endl;
    cout << treeAddress << " (result from tree data structure, " << duration2 << " microseconds)" << endl;

    cout << "\nHappy travels!" << endl;

    return 0;
}