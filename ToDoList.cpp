#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Task
{
public:
    int id;
    string title;
    string status;

    Task(int i, string t, string s = "Pending")
    {
        id = i;
        title = t;
        status = s;
    }
};

void saveTasks(vector<Task>& tasks)
{
    ofstream file("tasks.txt");

    for (Task t : tasks)
    {
        file << t.id << "|" << t.title << "|" << t.status << endl;
    }

    file.close();
}

void loadTasks(vector<Task>& tasks)
{
    ifstream file("tasks.txt");

    int id;
    string title, status;

    while (file >> id)
    {
        file.ignore();
        getline(file, title, '|');
        getline(file, status);

        tasks.push_back(Task(id, title, status));
    }

    file.close();
}

void addTask(vector<Task>& tasks)
{
    int id;
    string title;

    cout << "\nEnter Task ID: ";
    cin >> id;

    cin.ignore();

    cout << "Enter Task: ";
    getline(cin, title);

    tasks.push_back(Task(id, title));

    saveTasks(tasks);

    cout << "Task added successfully!\n";
}

void viewTasks(vector<Task>& tasks)
{
    if (tasks.empty())
    {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n========== TASKS ==========\n";

    for (Task t : tasks)
    {
        cout << "ID     : " << t.id << endl;
        cout << "Task   : " << t.title << endl;
        cout << "Status : " << t.status << endl;
        cout << "---------------------------\n";
    }
}

void searchTask(vector<Task>& tasks)
{
    int id;

    cout << "\nEnter Task ID to search: ";
    cin >> id;

    for (Task t : tasks)
    {
        if (t.id == id)
        {
            cout << "\nTask Found!\n";
            cout << "ID     : " << t.id << endl;
            cout << "Task   : " << t.title << endl;
            cout << "Status : " << t.status << endl;
            return;
        }
    }

    cout << "Task not found.\n";
}

void updateTask(vector<Task>& tasks)
{
    int id;
    string newTitle;

    cout << "\nEnter Task ID to update: ";
    cin >> id;

    cin.ignore();

    for (Task& t : tasks)
    {
        if (t.id == id)
        {
            cout << "Enter new task: ";
            getline(cin, newTitle);

            t.title = newTitle;

            saveTasks(tasks);

            cout << "Task updated successfully!\n";
            return;
        }
    }

    cout << "Task not found.\n";
}

void completeTask(vector<Task>& tasks)
{
    int id;

    cout << "\nEnter Task ID: ";
    cin >> id;

    for (Task& t : tasks)
    {
        if (t.id == id)
        {
            t.status = "Completed";

            saveTasks(tasks);

            cout << "Task marked as completed!\n";
            return;
        }
    }

    cout << "Task not found.\n";
}

void deleteTask(vector<Task>& tasks)
{
    int id;

    cout << "\nEnter Task ID: ";
    cin >> id;

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].id == id)
        {
            tasks.erase(tasks.begin() + i);

            saveTasks(tasks);

            cout << "Task deleted successfully!\n";
            return;
        }
    }

    cout << "Task not found.\n";
}

int main()
{
    vector<Task> tasks;

    loadTasks(tasks);

    int choice;

    do
    {
        cout << "\n========== TO-DO LIST ==========\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Search Task\n";
        cout << "4. Update Task\n";
        cout << "5. Mark Task Completed\n";
        cout << "6. Delete Task\n";
        cout << "7. Exit\n";
        cout << "================================\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTask(tasks);
            break;

        case 2:
            viewTasks(tasks);
            break;

        case 3:
            searchTask(tasks);
            break;

        case 4:
            updateTask(tasks);
            break;

        case 5:
            completeTask(tasks);
            break;

        case 6:
            deleteTask(tasks);
            break;

        case 7:
            cout << "\nThank you!\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}
