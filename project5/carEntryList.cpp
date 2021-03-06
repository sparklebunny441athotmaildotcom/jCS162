#include "headers.h"

carEntryList::carEntryList()
{
    head = NULL;
    tail = NULL;
    size = 0;
}

carEntryList::carEntryList(char fileName[])
{ 
    head = NULL;
    tail = NULL;
    size = 0;
    ifstream inFile;
    carEntry thisCar;
    char tempName[MAX_CHAR];
    double tempMpg;
    int tempCylinders;
    double tempDisplacement;
    double tempHorsepower;
    double tempWeight;
    double tempAcceleration;
    int tempModel;
    char originDesc[MAX_CHAR];
    whereFrom tempOrigin;

    inFile.open(fileName);
    if(!inFile)
    {
        cout << "Cannot open file! Exiting!!" << endl;
        exit(0);
    }
	while(!inFile.eof())
	{
        inFile.getline(tempName, MAX_CHAR, ';');
        inFile >> tempMpg;
        inFile.ignore(MAX_CHAR, ';');
        inFile >> tempCylinders;
        inFile.ignore(MAX_CHAR, ';');
        inFile >> tempDisplacement;
        inFile.ignore(MAX_CHAR, ';');
        inFile >> tempHorsepower;
        inFile.ignore(MAX_CHAR, ';');
        inFile >> tempWeight;
        inFile.ignore(MAX_CHAR, ';');
        inFile >> tempAcceleration;
        inFile.ignore(MAX_CHAR, ';');
        inFile >> tempModel;
		inFile.ignore(MAX_CHAR, ';');
        //getline to get raw string, read it with readOrigin
        inFile.getline(originDesc, MAX_CHAR, '\n');
        tempOrigin = readOrigin(originDesc[0]);
		//populate carEntry;
		thisCar.setCarName(tempName);
		thisCar.setMPG(tempMpg);
		thisCar.setCylinders(tempCylinders);
		thisCar.setDisplacement(tempDisplacement);
		thisCar.setHorsepower(tempHorsepower);
		thisCar.setWeight(tempWeight);
		thisCar.setAcceleration(tempAcceleration);
		thisCar.setModel(tempModel);
		thisCar.setOrigin(tempOrigin);
		addEntry(thisCar);
        //starts the loop again
        if(inFile.peek() == EOF)
        {
            break;
        }
	}
	inFile.close();

}

//destructor
carEntryList::~carEntryList()
{
    //KABOOM!!
    Node *current = head;
    while(current)
    {
        head = current->next;
        delete current;
        current = head;
    }
    tail = NULL;
}
//TODO delete these values???
void carEntryList::addEntry(carEntry thisCar)
{
    Node *newNode = NULL, *current = NULL, *prev = NULL;
	char str1[MAX_CHAR], str2[MAX_CHAR];
	//populate newNode
	newNode = new Node;
	newNode->data = thisCar;
	newNode->next = NULL;
	//check to see if list is empty
	if(!head)
	{
		head = newNode;
		tail = newNode;
	}
	//if list is not empty, then insert sorted by title
	else
	{
		current = head;
		current->data.getCarName(str1);
		newNode->data.getCarName(str2);
		while(current && isLessThan(str1, str2))
		{
			prev = current;
			current = current->next;
			if(current)
			{
				current->data.getCarName(str1);
			}
		}
		//check to see if we are at the end of our list
		if(!current)
        {
        	tail->next = newNode;
            tail = newNode;
        }
        //insert in between
        else if(prev)
        {
            newNode->next = current;
            prev->next = newNode;
        }
        //insert at the beginning
        else
        {
            newNode->next = current;
            head = newNode;
        }
        size++;
	}
    
}



void carEntryList::removeEntry()
{
	int delIndex = 1;
    int toRemove = 0;
    if(!size)
    {
        cout << "NOTHING TO DELETE!" << endl;
        return;
    }
	toRemove = readInt("Which car would you like to remove? (select by number) ");
	Node *current = head, *prev = NULL;
	while(toRemove < 1 || toRemove > size+1)
    {
		toRemove = readInt("Invalid Index! please enter a number between 1 and the max list size: ");
	}
	while(current && delIndex < toRemove)
    {
		prev = current;
		current = current->next;
		delIndex++;
	}
	if(!prev)
    {
		head = current->next;
	} 
    else if(current == tail)
    {
		prev->next = current->next;
		tail = prev;
	} 
    else 
    {
		prev->next = current->next;
	}
	delete current;
	current = NULL;
	prev = NULL;
	size--;
}

void carEntryList::displayList()
{
    int count = 1;
    Node *current;
	for(current = head; current; current = current->next)
	{
		cout << count << ") ";
        current->data.printCarEntry();
        count++;
	}
	cout << endl;
}

int carEntryList::getSize()
{
    return size;
}

void carEntryList::searchByName()
{
    
	char searchName[MAX_CHAR];
	char tempName[MAX_CHAR];
    bool flag = false;
	cout << "Please enter the name of the car you would like to search for (can be a partial match):";
	cin.get(searchName, MAX_CHAR);
	convertCase(searchName);
	for(Node *current = head; current; current  = current->next)
	{
		current->data.getCarName(tempName);
		convertCase(tempName);
		if(strstr(tempName, searchName) != NULL)
		{
			current->data.printCarEntry();
			flag = true;
		}
	}
    if(!flag)
    {
        cout << "No cars matching this search can be found :( " << endl;
    }
    return;
}

void carEntryList::searchByOrigin()
{
    char firstLetter;
    whereFrom searchOrigin;
    whereFrom tempOrigin;
    bool flag = false;
    int index = 1;
    cout << "Please select a filter to display cars from a particular region: [U]sa, [E]urope, [J]apan";
    cin >> firstLetter;
    searchOrigin = readOrigin(firstLetter);
    for(Node *current = head; current; current = current->next)
    {
        tempOrigin = current->data.getOrigin();
        if(searchOrigin == tempOrigin)
        {
            cout << index << ") ";
            current->data.printCarEntry();
            flag = true;
        }
        index++;
    }
    if(!flag)
    {
        cout << "No entries match this search parameter! " << endl;
    }
    return;
}

void carEntryList::searchByMPG()
{
    double tempMPG;
    double selectedMPG;
    int index = 1;
    bool flag = false;
    cout << "Please enter the minimum number of miles per gallon: " << endl;
    cin >> selectedMPG;
    while(!cin)
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Please enter a number!  ";
        cin >> selectedMPG;
    }
    for(Node *current = head; current; current = current->next)
    {
        tempMPG = current->data.getMPG();
        if(tempMPG >= selectedMPG)
        {
            cout << index << ") ";
            current->data.printCarEntry();
            flag = true;
            index++;
        }
    }
    if(!flag)
    {
        cout << "No cars in this list have an MPG rating above this number! " << endl;
    }
}

//writes the data to the file
void carEntryList::writeAndQuit(char fileName[])
{
	ofstream outFile;
	outFile.open(fileName);
    Node *current;
	for(current = head; current; current = current->next)
	{
        current->data.printCarEntry(outFile);
	}
    return;
}


//function to compare 2 strings
bool carEntryList::isLessThan(char str1[], char str2[])
{
	if(strcmp(str1, str2) < 0)
		return true;
	return false;
}
