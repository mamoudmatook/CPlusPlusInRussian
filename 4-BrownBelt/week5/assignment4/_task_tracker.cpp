// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
// Перечислимый тип для статуса задачиl
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
using namespace std;
// enum class TaskStatus
// {
//     NEW,         // новая
//     IN_PROGRESS, // в разработке
//     TESTING,     // на тестировании
//     DONE         // завершена
// };

using TasksInfo = map<TaskStatus, int>;

TaskStatus Next(TaskStatus task_status)
{
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

void RemoveZeros(TasksInfo &tasks_info)
{
    vector<TaskStatus> statuses_to_remove;
    for (const auto &task_item : tasks_info)
    {
        if (task_item.second == 0)
        {
            statuses_to_remove.push_back(task_item.first);
        }
    }
    for (const TaskStatus status : statuses_to_remove)
    {
        tasks_info.erase(status);
    }
}

class TeamTasks
{
public:
    const TasksInfo &GetPersonTasksInfo(const string &person) const
    {
        return person_task_.at(person);
    }

    void AddNewTask(const string &person)
    {
        ++person_task_[person][TaskStatus::NEW];
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string &person, int task_count)
    {
        TasksInfo &current_info = person_task_[person];
        TasksInfo updated_info, old_info;
        for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status))
        {
            updated_info[Next(status)] = min(task_count, current_info[status]);
            task_count -= updated_info[Next(status)];
        }
        for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status))
        {
            old_info[status] = current_info[status] - updated_info[Next(status)];
            current_info[status] += updated_info[status] - updated_info[Next(status)];
        }
        current_info[TaskStatus::DONE] += updated_info[TaskStatus::DONE];
        RemoveZeros(current_info);
        RemoveZeros(old_info);
        RemoveZeros(updated_info);
        return {updated_info, old_info};
    }

private:
    unordered_map<string, TasksInfo> person_task_;
};

// void PrintTasksInfo(TasksInfo tasks_info)
// {
//     cout << tasks_info[TaskStatus::NEW] << " new tasks"
//          << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
//          << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
//          << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
// }

// int main()
// {
//     TeamTasks tasks;
//     tasks.AddNewTask("Ilia");
//     for (int i = 0; i < 3; ++i)
//     {
//         tasks.AddNewTask("Ivan");
//     }
//     cout << "Ilia's tasks: ";
//     PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//     cout << "Ivan's tasks: ";
//     PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

//     TasksInfo updated_tasks, untouched_tasks;

//     tie(updated_tasks, untouched_tasks) =
//         tasks.PerformPersonTasks("Ivan", 2);
//     cout << "Updated Ivan's tasks: ";
//     PrintTasksInfo(updated_tasks);
//     cout << "Untouched Ivan's tasks: ";
//     PrintTasksInfo(untouched_tasks);

//     tie(updated_tasks, untouched_tasks) =
//         tasks.PerformPersonTasks("Ivan", 2);
//     cout << "Updated Ivan's tasks: ";
//     PrintTasksInfo(updated_tasks);
//     cout << "Untouched Ivan's tasks: ";
//     PrintTasksInfo(untouched_tasks);

//     return 0;
// }

/*

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
[{"DONE": 1}, {"TESTING": 4}]
[]
[{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
[{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
{"NEW": 0, "IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}

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
 (Time used: 0.00/1.00, preprocess time used: 0/None, memory used: 48103424/536870912.)
*/