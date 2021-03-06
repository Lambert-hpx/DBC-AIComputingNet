/*********************************************************************************
*  Copyright (c) 2017-2018 DeepBrainChain core team
*  Distributed under the MIT software license, see the accompanying
*  file COPYING or http://www.opensource.org/licenses/mit-license.php
* file name        :   container_client.h
* description    :   container client for definition
* date                  :   2018.04.04
* author            :   Bruce Feng
**********************************************************************************/

#pragma once

#include <memory>
#include <string>
#include "http_client.h"
#include "container_message.h"


using namespace std;


#define DEFAULT_STOP_CONTAINER_TIME                         2                              //stop time out


namespace matrix
{
    namespace core
    { 

        class container_client
        {
        public:

            container_client(std::string remote_ip, uint16_t remote_port);

            ~container_client() = default;

            //create
            std::shared_ptr<container_create_resp> create_container(std::shared_ptr<container_config> config);

            std::shared_ptr<container_create_resp> create_container(std::shared_ptr<container_config> config, std::string name,std::string autodbcimage_version);
            int32_t rename_container(std::string name,std::string autodbcimage_version);
            int32_t restart_container(std::string container_id);
            int32_t update_container(std::string container_id, std::shared_ptr<update_container_config> config);
            std::string get_commit_image(std::string container_id,std::string version,std::string task_id,int32_t sleep_time);
            //start
            int32_t start_container(std::string container_id);

            int32_t start_container(std::string container_id, std::shared_ptr<container_host_config> config);

            //stop
            int32_t stop_container(std::string container_id);

            int32_t stop_container(std::string container_id, int32_t timeout);

            //wait
            int32_t wait_container(std::string container_id);

            //remove
            int32_t remove_container(std::string container_id);

            int32_t remove_container(std::string container_id, bool remove_volumes);

            //prune container
            int32_t prune_container(int16_t interval);

            int32_t prune_images();
            int32_t delete_image(std::string id);
            std::shared_ptr<images_info> get_images();
            //inspect
            std::shared_ptr<container_inspect_response> inspect_container(std::string container_id);
            bool  can_delete_image(std::string image_id);
            //logs
            std::shared_ptr<container_logs_resp> get_container_log(std::shared_ptr<container_logs_req> req);
            std::string get_image_id(std::string container_id);
            int32_t remove_image(std::string image_id);
            void set_address(std::string remote_ip, uint16_t remote_port);

            int32_t exist_docker_image(const std::string & image_name,int32_t sleep_time);

            std::shared_ptr<docker_info> get_docker_info();
            std::string get_container(const std::string user_container_name);
            std::string get_running_container();
            void del_images();
            int32_t exist_container(const std::string & container_name);
            std::string get_container_id(std::string container_name);
            std::string commit_image(std::string container_id,std::string version,std::string task_id,int32_t sleep_time);
            int32_t exist_container_time(const std::string & container_name,int32_t sleep_time);
            std::string get_container_size(std::string id);
            std::string get_running_container_no_size();
            std::string get_container_id_current(std::string task_id);
            std::string get_container_size_by_task_id(std::string id);
            std::string get_images_original();
        protected:

            http_client m_http_client;

            std::string m_remote_ip;

            uint16_t m_remote_port;

            std::shared_ptr<docker_info> m_docker_info_ptr;

          //  std::shared_ptr<images_info> m_list_images_info_ptr;
        };

    }

}
