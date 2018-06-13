/*********************************************************************************
*  Copyright (c) 2017-2018 DeepBrainChain core team
*  Distributed under the MIT software license, see the accompanying
*  file COPYING or http://www.opensource.org/licenses/mit-license.php
* file name        :   ai_power_provider_service.h
* description    :   ai_power_provider_service
* date                  :   2018.04.05
* author            :   Bruce Feng
**********************************************************************************/
#pragma once


#include <leveldb/db.h>
#include <string>
#include "service_module.h"
#include "db_types.h"
#include "container_client.h"
#include "task_common_def.h"


using namespace matrix::core;
using namespace boost::asio::ip;


#define AI_TRAINING_TASK_TIMER                                      "training_task"
#define AI_TRAINING_TASK_TIMER_INTERVAL                 (30 * 1000)                                                 //30s timer
#define AI_TRAINING_MAX_RETRY_TIMES                                  4

#define AI_TRAINING_TASK_SCRIPT_HOME                         "/"
#define AI_TRAINING_TASK_SCRIPT                                       "dbc_task.sh"                                            //training shell script name

//gpu env
#define AI_TRAINING_ENV_PATH                                            "PATH=/usr/local/nvidia/bin:/usr/local/cuda/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
#define AI_TRAINING_LD_LIBRARY_PATH                            "LD_LIBRARY_PATH=/usr/local/cuda/extras/CUPTI/lib64:/usr/local/nvidia/lib:/usr/local/nvidia/lib64"
#define AI_TRAINING_NVIDIA_VISIBLE_DEVICES              "NVIDIA_VISIBLE_DEVICES=all"
#define AI_TRAINING_NVIDIA_DRIVER_CAPABILITIES     "NVIDIA_DRIVER_CAPABILITIES=compute,utility"
#define AI_TRAINING_LIBRARY_PATH                                    "LIBRARY_PATH=/usr/local/cuda/lib64/stubs:"
#define AI_TRAINING_MOUNTS_SOURCE                              "/var/lib/nvidia-docker/volumes/nvidia_driver/384.111"
#define AI_TRAINING_MOUNTS_DESTINATION                  "/usr/local/nvidia"
#define AI_TRAINING_MOUNTS_MODE                                  "ro"
#define AI_TRAINING_CGROUP_PERMISSIONS                   "rwm"

#define DEFAULT_SPLIT_COUNT                                                         2
#define DEFAULT_NVIDIA_DOCKER_PORT                                                3476

namespace ai
{
	namespace dbc
	{

        enum container_status
        {
            container_unknown = 0,
            container_running,
            container_closed
        };

        struct task_time_stamp_comparator
        {
            bool operator() (const std::shared_ptr<ai_training_task> & t1, const std::shared_ptr<ai_training_task> & t2) const
            {
                return t1->received_time_stamp < t2->received_time_stamp;
            }
        };

        class nvidia_config
        {
        public:

            std::string driver_name;

            std::string volume;

            std::list<std::string> devices;
        };

        class ai_power_provider_service : public service_module
        {
        public:

            ai_power_provider_service();

            virtual ~ai_power_provider_service() = default;

            virtual std::string module_name() const { return ai_power_provider_service_name; }

        protected:

            int32_t init_conf();

            void init_subscription();

            void init_invoker();

            void init_timer();

            int32_t init_db();

            int32_t service_init(bpo::variables_map &options);

            int32_t service_exit();

        protected:

            int32_t on_start_training_req(std::shared_ptr<message> &msg);

            int32_t on_stop_training_req(std::shared_ptr<message> &msg);

            int32_t on_list_training_req(std::shared_ptr<message> &msg);

            int32_t on_logs_req(const std::shared_ptr<message> &msg);

            std::string format_logs(const std::string  &raw_logs, uint16_t max_lines);

        protected:

            //ai power provider service

            std::shared_ptr<nvidia_config> get_nividia_config_from_cli();

            std::shared_ptr<container_config> get_container_config(std::shared_ptr<ai_training_task> task);

            int32_t on_training_task_timer(std::shared_ptr<core_timer> timer);

            int32_t start_exec_training_task(std::shared_ptr<ai_training_task> task);

            int32_t check_training_task_status(std::shared_ptr<ai_training_task> task);

            int32_t write_task_to_db(std::shared_ptr<ai_training_task> task);

            int32_t load_task_from_db();            

        protected:

            std::shared_ptr<leveldb::DB> m_prov_training_task_db;

            std::string m_container_ip;

            uint16_t m_container_port;

            std::string m_container_image;

            std::shared_ptr<container_client> m_container_client;

            std::shared_ptr<container_client> m_nvidia_client;

            std::unordered_map<std::string, std::shared_ptr<ai_training_task>> m_training_tasks;             //ai power provider cached training task in memory

            std::list<std::shared_ptr<ai_training_task>> m_queueing_tasks;

            uint32_t m_training_task_timer_id;

            std::shared_ptr<nvidia_config> m_nv_config;

        };

	}

}



