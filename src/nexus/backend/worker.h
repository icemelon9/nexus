#ifndef NEXUS_BACKEND_WORKER_H_
#define NEXUS_BACKEND_WORKER_H_

#include <memory>
#include <string>
#include <thread>

#include "nexus/common/block_queue.h"
#include "nexus/backend/gpu_executor.h"
#include "nexus/backend/task.h"

namespace nexus {
namespace backend {

class BackendServer;

class Worker {
 public:
  Worker(int index, BackendServer* server,
         BlockPriorityQueue<Task>& task_queue,
         GpuExecutor* gpu_executor);

  void Start();

  void Stop();

  void Run();

 private:
  void Process(std::shared_ptr<Task> task);

  void SendReply(std::shared_ptr<Task> task);

 private:
  int index_;
  BackendServer* server_;
  BlockPriorityQueue<Task>& task_queue_;
  GpuExecutor* gpu_executor_;
  volatile bool running_;
  std::thread thread_;
};

} // namespace backend
} // namespace nexus

#endif // NEXUS_BACKEND_WORKER_H_
