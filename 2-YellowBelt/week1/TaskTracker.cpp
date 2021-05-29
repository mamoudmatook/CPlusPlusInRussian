/***
The PerformPersonTasks method must implement the following algorithm:

Consider all the outstanding tasks of the person developer.
Let's sort them by statuses: first, all tasks in the NEW status, then all tasks in the IN_PROGRESS status, and finally, tasks in the TESTING status.
Let's consider the first task_count tasks and transfer each of them to the following status in accordance with the natural order: NEW → IN_PROGRESS → TESTING → DONE.
Let's return a tuple of two elements: information about the statuses of the updated tasks (including those that ended up in the DONE status) and information about the statuses of the remaining uncompleted tasks.
If there is no developer named person, the PerformPersonTasks method should return a tuple of two empty TasksInfo

It is guaranteed that task_count is positive. If task_count exceeds the current number of uncompleted tasks of the developer, it is sufficient to assume that task_count is equal to the number of uncompleted tasks: in this case, you do not need to update the status of any task twice.

In addition, it is guaranteed that the GetPersonTasksInfo method will not be called for a developer who has no tasks.

An example of the PerformPersonTasks method
Let's assume that a particular developer has 10 tasks with the following statuses:

NEW — 3
IN_PROGRESS — 2
TESTING — 4
DONE — 1
The PerformPersonTasks command is received with the task_count = 4 parameter, which means the status update for 3 tasks from NEW to IN_PROGRESS and for 1 task from IN_PROGRESS to TESTING. If you write out the statuses of all tasks in order, and enclose the updated ones in square brackets, then the change can be represented as follows: [NEW, NEW, NEW, IN_PROGRESS,] IN_PROGRESS, TESTING, TESTING, TESTING, TESTING, DONE ==> [IN_PROGRESS, IN_PROGRESS , IN_PROGRESS, TESTING,] IN_PROGRESS, TESTING, TESTING, TESTING, TESTING, DONE

Thus, the new task statuses will be as follows:

IN_PROGRESS - 3 updated, 1 old
TESTING - 1 updated, 4 old
DONE - 1 old
In this case, you need to return a tuple of 2 dictionaries:

Updated tasks: IN_PROGRESS - 3, TESTING - 1.
Tasks not updated, excluding completed ones: IN_PROGRESS - 1, TESTING - 4.
None of the dictionaries should contain unnecessary elements, that is, statuses that correspond to zero tasks.

By convention, DONE tasks do not need to be returned in untouched tasks (untouched_tasks).

Note
Updating a dictionary while iterating over it can lead to unpredictable consequences. If such a need arises, it is recommended to first collect information about the updates in a separate temporary dictionary, and then apply them to the main dictionary.

***/
/***
Input:
AddNewTasks Alice 5
PerformPersonTasks Alice 5
PerformPersonTasks Alice 5
PerformPersonTasks Alice 1
AddNewTasks Alice 5
PerformPersonTasks Alice 2
GetPersonTasksInfo Alice
PerformPersonTasks Alice 4
GetPersonTasksInfo Alice

Your output:
[]
[{"IN_PROGRESS": 5}, {}]
[{"TESTING": 5}, {}]
[{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]
[]
[{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}, {"NEW": 3, "TESTING": 4}]
{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
[{"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
{"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}

Correct output:
[]
[{"IN_PROGRESS": 5}, {}]
[{"TESTING": 5}, {}]
[{"DONE": 1}, {"TESTING": 4}]
[]
[{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
[{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
{"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
***/

#include <iostream>
#include <map>
#include <vector>
using namespace std;
// enum class TaskStatus
// {
//     NEW,         // новая
//     IN_PROGRESS, // в разработке
//     TESTING,     // на тестировании
//     DONE         // завершена
// };

// // Объявляем тип-синоним для map<TaskStatus, int>,
// // позволяющего хранить количество задач каждого статуса
// using TasksInfo = map<TaskStatus, int>;

class TeamTasks
{
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const
    {
        return team.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person)
    {
        team[person][TaskStatus::NEW] += 1;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo>
    PerformPersonTasks(const string &person, int task_count)
    {
        if (team.count(person) == 0)
        {
            TasksInfo a, b;
            return make_tuple(a, b);
        }
        TasksInfo updated, untouched, upgraded;
        auto task_status = team[person];
        for (const auto &status : task_status)
        {
            switch (status.first)
            {
            case TaskStatus::NEW:
                if (status.second > 0)
                {
                    auto new_tasks = status.second;
                    for (int i = 0; i < task_count && new_tasks > 0; --task_count, --new_tasks)
                    {
                        ++updated[TaskStatus::IN_PROGRESS];
                        ++upgraded[TaskStatus::IN_PROGRESS];
                    }
                    if (new_tasks)
                    {
                        untouched[TaskStatus::NEW] += new_tasks;
                        upgraded[TaskStatus::NEW] += new_tasks;
                    }
                }
                break;
            case TaskStatus::IN_PROGRESS:
                if (status.second > 0)
                {
                    auto new_tasks = status.second;
                    for (int i = 0; i < task_count && new_tasks > 0; --task_count, --new_tasks)
                    {
                        ++updated[TaskStatus::TESTING];
                        ++upgraded[TaskStatus::TESTING];
                    }
                    if (new_tasks)
                    {
                        untouched[TaskStatus::IN_PROGRESS] += new_tasks;
                        upgraded[TaskStatus::IN_PROGRESS] += new_tasks;
                    }
                }
                break;
            case TaskStatus::TESTING:
                if (status.second > 0)
                {
                    auto new_tasks = status.second;
                    for (int i = 0; i < task_count && new_tasks > 0; --task_count, --new_tasks)
                    {
                        ++updated[TaskStatus::DONE];
                        ++upgraded[TaskStatus::DONE];
                    }
                    if (new_tasks)
                    {
                        untouched[TaskStatus::TESTING] += new_tasks;
                        upgraded[TaskStatus::TESTING] += new_tasks;
                    }
                }
                break;

            default:
                if (status.second > 0)
                {
                    upgraded[TaskStatus::DONE] += status.second;
                }
                break;
            }
        }
        team[person] = upgraded;
        return make_tuple(updated, untouched);
    }

private:
    map<string, TasksInfo> team;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info)
{
    cout << tasks_info[TaskStatus::NEW] << " new tasks"
         << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
         << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
         << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main()
{
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i)
    {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
