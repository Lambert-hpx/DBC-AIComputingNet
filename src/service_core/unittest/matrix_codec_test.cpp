#include <boost/test/unit_test.hpp>

namespace utf = boost::unit_test;

#include "codec/matrix_coder.h"
#include "service_message_id.h"
#include <iostream>
#include <memory>

using namespace matrix::service_core;

BOOST_AUTO_TEST_CASE(test_encode_shake_hand){

    message msg;
    channel_handler_context ctx;
    byte_buf buf;

    matrix_coder coder;

    msg.header.msg_name = SHAKE_HAND_REQ;
    msg.header.msg_priority = 0;

    auto req_content = std::make_shared<shake_hand_req>();
    req_content->header.__set_magic(TEST_NET);
    req_content->header.__set_msg_name(SHAKE_HAND_REQ);
    req_content->header.__set_nonce("12345");

    msg.set_content(req_content);

    auto r = coder.encode(ctx, msg, buf);

    std::cout<<"buf: "<< buf.to_string()<<std::endl;
    BOOST_TEST(r==ENCODE_SUCCESS);
}

    BOOST_AUTO_TEST_CASE(test_encode){

        message msg;
        channel_handler_context ctx;
        byte_buf buf;

        matrix_coder coder;

        msg.header.msg_name = P2P_GET_PEER_NODES_RESP;
        msg.header.msg_priority = 0;

        auto resp_content = std::make_shared<get_peer_nodes_resp>();
        resp_content->header.__set_magic(TEST_NET);
        resp_content->header.__set_msg_name(P2P_GET_PEER_NODES_RESP);
        resp_content->header.__set_nonce("12345");

        matrix::service_core::peer_node_info info;
        info.peer_node_id = "node1";
        info.live_time_stamp = 1;
        info.addr.ip = "192.168.0.2";
        info.addr.port = 10001;
        info.service_list.push_back(std::string("ai_training"));

        std::vector<peer_node_info>  peer_nodes_list;
        peer_nodes_list.push_back(info);
        resp_content->body.__set_peer_nodes_list(peer_nodes_list);

        msg.set_content(resp_content);

        auto r = coder.encode(ctx, msg, buf);

        std::cout<<"compress: "<< buf.to_string()<<std::endl;
        BOOST_TEST(r==ENCODE_SUCCESS);

    }

    BOOST_AUTO_TEST_CASE(test_encode_wo_required_field){

        message msg;
        channel_handler_context ctx;
        byte_buf buf;

        matrix_coder coder;

        msg.header.msg_name = P2P_GET_PEER_NODES_RESP;
        msg.header.msg_priority = 0;

        auto resp_content = std::make_shared<get_peer_nodes_resp>();
//        resp_content->header.magic = TEST_NET;
//        resp_content->header.msg_name = P2P_GET_PEER_NODES_RESP;
        resp_content->header.__set_nonce("12345");

        matrix::service_core::peer_node_info info;
        info.peer_node_id = "node1";
        info.live_time_stamp = 1;
        info.addr.ip = "192.168.0.2";
        info.addr.port = 10001;
        info.service_list.push_back(std::string("ai_training"));

        std::vector<peer_node_info>  peer_nodes_list;
        peer_nodes_list.push_back(info);
        resp_content->body.__set_peer_nodes_list(peer_nodes_list);

        msg.set_content(resp_content);

        auto r = coder.encode(ctx, msg, buf);

        std::cout<<"buf: "<< buf.to_string()<<std::endl;
        BOOST_TEST(r==ENCODE_SUCCESS);

    }


    #include <cstdint>


// tips: generate bytes for c++ from message dump
//    python
//    s="00 00 00 80 00 00 00 00 7F 7F".split(" ")
//    s=["0x"+e for e in s]
//    ",".join(s)
    BOOST_AUTO_TEST_CASE(test_decode){
        channel_handler_context ctx;
        byte_buf buf;

        const uint8_t b[]={0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
                  0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x73, 0x68, 0x61, 0x6B, 0x65, 0x5F, 0x68, 0x61,
                  0x6E, 0x64, 0x5F, 0x72, 0x65, 0x73, 0x70, 0x7F, 0x7F};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(msg->header.msg_name == "shake_hand_resp");
        BOOST_TEST(r==DECODE_SUCCESS);

    }

    BOOST_AUTO_TEST_CASE(test_decode_missing_T_STOP){
        channel_handler_context ctx;
        byte_buf buf;

        const uint8_t b[]={0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
                  0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x73, 0x68, 0x61, 0x6B, 0x65, 0x5F, 0x68, 0x61,
                  0x6E, 0x64, 0x5F, 0x72, 0x65, 0x73, 0x70};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(r==DECODE_ERROR);
    }

    BOOST_AUTO_TEST_CASE(test_decode_empty_required_field){
        channel_handler_context ctx;
        byte_buf buf;

        const uint8_t b[]={0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x08,0x00,0x01,0x00,0x00,0x00,0x00,
                           0x0B,0x00,0x02,0x00,0x00,0x00,0x00,
                           0x0B,0x00,0x03,0x00,0x00,0x00,0x05,0x31,0x32,0x33,0x34,0x35,0x7F,
                           0x0F,0x00,0x01,0x0C,0x00,0x00,0x00,0x01,0x0B,0x00,0x01,0x00,0x00,0x00,0x05,0x6E,0x6F,0x64,0x65,0x31,0x08,0x00,0x02,0x00,0x00,0x00,0x00,0x08,0x00,0x03,0x00,0x00,0x00,0x00,0x08,0x00,0x04,0x00,0x00,0x00,0x01,0x0C,0x00,0x05,0x0B,0x00,0x01,0x00,0x00,0x00,0x0B,0x31,0x39,0x32,0x2E,0x31,0x36,0x38,0x2E,0x30,0x2E,0x32,0x06,0x00,0x02,0x27,0x11,0x7F,0x0F,0x00,0x06,0x0B,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x0B,0x61,0x69,0x5F,0x74,0x72,0x61,0x69,0x6E,0x69,0x6E,0x67,0x7F,0x7F};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(msg->header.msg_name == "unknown message");
        BOOST_TEST(r==DECODE_UNKNOWN_MSG);
    }

    BOOST_AUTO_TEST_CASE(test_decode_abnormal_packet_length){
        channel_handler_context ctx;
        byte_buf buf;

        const uint8_t b[]={0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
                           0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x73, 0x68, 0x61, 0x6B, 0x65, 0x5F, 0x68, 0x61,
                           0x6E, 0x64, 0x5F, 0x72, 0x65, 0x73, 0x70};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(r==DECODE_ERROR);
    }

    BOOST_AUTO_TEST_CASE(test_decode_extremely_long_packet){
        channel_handler_context ctx;
        byte_buf buf;

#if 0
        const uint8_t b[]={0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
                           0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x73, 0x68, 0x61, 0x6B, 0x65, 0x5F, 0x68, 0x61,
                           0x6E, 0x64, 0x5F, 0x72, 0x65, 0x73, 0x70, 0x7F, 0x7F};
#endif

        uint8_t c[1024000]={0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97};

        for(uint32_t i=15; i< sizeof(c); i++){
            c[i] =0x01;
        }


        buf.write_to_byte_buf((const char*)c, sizeof(c));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);


        BOOST_TEST(r!=DECODE_SUCCESS);
    }

    BOOST_AUTO_TEST_CASE(test_decode_extremely_short_packet){
        channel_handler_context ctx;
        byte_buf buf;

        const uint8_t b[]={0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
                           0x0B};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(r!=DECODE_SUCCESS);
    }

    BOOST_AUTO_TEST_CASE(test_decode_abnormal_string_length){
        channel_handler_context ctx;
        byte_buf buf;

        int i = 4;
        string text = "Player ";
        std::cout << "player" + std::to_string(i) <<std::endl;

        const uint8_t b[]={0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
                           0x0B, 0x00, 0x02, 0x0F, 0xFF, 0xFF, 0xFF, 0x73, 0x68, 0x61, 0x6B, 0x65, 0x5F, 0x68, 0x61,
                           0x6E, 0x64, 0x5F, 0x72, 0x65, 0x73, 0x70, 0x7F, 0x7F};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(r!=DECODE_SUCCESS);
    }

//    BOOST_AUTO_TEST_CASE(test_decode_list_recursive){
//        channel_handler_context ctx;
//        byte_buf buf;
//
//        const uint8_t b[]={0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
//                           0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x73, 0x68, 0x61, 0x6B, 0x65, 0x5F, 0x68, 0x61,
//                           0x6E, 0x64, 0x5F, 0x72, 0x65, 0x73, 0x70, 0x7F,
//                           0x0F, 0x00, 0x01, 0x0C, 0x00, 0x00, 0x00, 0x01,0x7F,
//                           0x7F};
//
//        buf.write_to_byte_buf((const char*)b, sizeof(b));
//
//        matrix_coder coder;
//
//        shared_ptr<message> msg = std::make_shared<message>();
//
//        decode_status r = coder.decode(ctx, buf, msg);
//
//        BOOST_TEST(r!=ENCODE_SUCCESS);
//    }

    BOOST_AUTO_TEST_CASE(test_decode_wo_msg_name_field){
        channel_handler_context ctx;
        byte_buf buf;

        const uint8_t b[]={0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0xE1, 0xD1, 0xA0, 0x97,
                           0x7F, 0x7F};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(r!=DECODE_SUCCESS);
    }

    BOOST_AUTO_TEST_CASE(test_decode_wo_magic_field){
        channel_handler_context ctx;
        byte_buf buf;

        const uint8_t b[]={0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00,
                           0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x73, 0x68, 0x61, 0x6B, 0x65, 0x5F, 0x68, 0x61,
                           0x6E, 0x64, 0x5F, 0x72, 0x65, 0x73, 0x70,
                           0x08, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01,
                           0x7F, 0x7F};

        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        BOOST_TEST(r!=DECODE_SUCCESS);
    }


    BOOST_AUTO_TEST_CASE(test_decode_get_peer_nodes_resp){
        channel_handler_context ctx;
        byte_buf buf;

//        const uint8_t b[] ={0x00,0x00,0x00,0xE3,0x00,0x00,0x00,0x00,0x08,0x00,0x01,0xE1,0xD1,0xA0,0x97,0x0B,0x00,0x02,0x00,0x00,0x00,0x07,0x76,0x65,0x72,0x5F,0x72,0x65,0x71,0x0B,0x00,0x03,0x00,0x00,0x00,0x31,0x72,0x66,0x48,0x6D,0x46,0x34,0x48,0x62,0x77,0x6F,0x36,0x38,0x57,0x76,0x69,0x5A,0x58,0x53,0x62,0x6D,0x47,0x6E,0x31,0x53,0x36,0x51,0x59,0x48,0x33,0x62,0x55,0x32,0x37,0x47,0x37,0x52,0x45,0x5A,0x5A,0x33,0x66,0x31,0x43,0x4A,0x6B,0x66,0x7A,0x5A,0x72,0x7F,0x0B,0x00,0x01,0x00,0x00,0x00,0x2B,0x32,0x67,0x66,0x70,0x70,0x33,0x4D,0x41,0x42,0x34,0x39,0x72,0x65,0x55,0x62,0x70,0x79,0x77,0x77,0x61,0x42,0x74,0x48,0x50,0x4E,0x6B,0x33,0x55,0x4D,0x70,0x48,0x34,0x36,0x62,0x4D,0x51,0x61,0x72,0x6E,0x4A,0x79,0x42,0x72,0x08,0x00,0x02,0x00,0x00,0x02,0x00,
//                            0x08,0x00,0x03,0x00,0x00,0x00,0x01,
//                            0x0A,0x00,0x04,0x00,0x00,0x00,0x00,0x5B,0x06,0x38,0x12,
//                            0x0C,0x00,0x05,
//                                 0x0B,0x00,0x01,0x00,0x00,0x00,0x07,0x30,0x2E,0x30,0x2E,0x30,0x2E,0x30,
//                                 0x06,0x00,0x02,0x2B,0x64,
//                                 0x7F,
//                            0x0C,0x00,0x06,
//                                 0x0B,0x00,0x01,0x00,0x00,0x00,
//                                 0x0F,0x31,0x39,0x32,0x2E,0x31,0x36,0x38,0x2E,0x31,0x30,0x30,0x2E,0x31,0x37,0x33,
//                                 0x06,0x00,0x02,0x52,0x74,
//                                 0x7F,
//                            0x0A,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F};


        const uint8_t b[] ={0x00,0x00,0x00,0xEA,0x00,0x00,0x00,0x00,0x08,0x00,0x01,0xE1,0xD1,0xA0,0x97,0x0B,0x00,0x02,0x00,0x00,0x00,0x13,0x67,0x65,0x74,0x5F,0x70,0x65,0x65,0x72,0x5F,0x6E,0x6F,0x64,0x65,0x73,0x5F,0x72,0x65,0x73,0x70,0x0B,0x00,0x03,0x00,0x00,0x00,0x32,0x32,0x33,0x4C,0x76,0x6D,0x36,0x5A,0x54,0x67,0x51,0x31,0x37,0x52,0x51,0x42,0x39,0x52,0x36,0x55,0x43,0x46,0x71,0x4A,0x31,0x6B,0x74,0x75,0x4A,0x52,0x64,0x79,0x55,0x44,0x43,0x58,0x54,0x74,0x47,0x48,0x70,0x44,0x62,0x75,0x56,0x6B,0x6A,0x50,0x44,0x65,0x4C,0x7F,0x0F,0x00,0x01,0x0C,0x00,0x00,0x00,0x01,0x0B,0x00,0x01,0x00,0x00,0x00,0x2B,0x32,0x67,0x66,0x70,0x70,0x33,0x4D,0x41,0x42,0x34,0x39,0x35,0x35,0x51,0x5A,0x4D,0x68,0x51,0x4D,0x50,0x35,0x6F,0x35,0x6A,0x35,0x43,0x41,0x6E,0x4D,0x79,0x61,0x65,0x6A,0x4A,0x71,0x36,0x55,0x70,0x65,0x36,0x44,0x74,0x48,0x08,0x00,0x02,0x00,0x00,0x00,0x00,0x08,0x00,0x03,0x00,0x00,0x00,0x00,0x08,0x00,0x04,0x00,0x00,0x00,0x00,0x0C,0x00,0x05,0x0B,0x00,0x01,0x00,0x00,0x00,0x0F,0x31,0x39,0x32,0x2E,0x31,0x36,0x38,0x2E,0x31,0x30,0x30,0x2E,0x31,0x37,0x33,0x06,0x00,0x02,0xF7,0xCD,0x7F,0x0F,0x00,0x06,0x0B,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x0B,0x61,0x69,0x5F,0x74,0x72,0x61,0x69,0x6E,0x69,0x6E,0x67,0x7F,0x7F};
        buf.write_to_byte_buf((const char*)b, sizeof(b));

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

        std::cout<<"msg name: " << msg->content->header.msg_name <<std::endl;



        BOOST_TEST(r == DECODE_SUCCESS);

        auto r2 = coder.encode(ctx, *msg, buf);
        std::cout<<"buf: "<< buf.to_string()<<std::endl;
        BOOST_TEST(r2==ENCODE_SUCCESS);
    }

BOOST_AUTO_TEST_CASE(test_encode_compact_shake_hand){

    message msg;
    channel_handler_context ctx;
    byte_buf buf;

    matrix_coder coder;

    msg.header.msg_name = SHAKE_HAND_REQ;
    msg.header.msg_priority = 0;

    auto req_content = std::make_shared<shake_hand_req>();
    req_content->header.__set_magic(TEST_NET);
    req_content->header.__set_msg_name(SHAKE_HAND_REQ);
    req_content->header.__set_nonce("12345");

    msg.set_content(req_content);

    auto r = coder.encode(ctx, msg, buf);

    std::cout<<"buf: "<< buf.to_string()<<std::endl;
    BOOST_TEST(r==ENCODE_SUCCESS);
}


BOOST_AUTO_TEST_CASE(test_decode_compact){
    channel_handler_context ctx;
    byte_buf buf;

    const uint8_t b[] ={0x00,0x00,0x00,0xB6,0x00,0x00,0x00,0x01,0x15,0xCD,0xFD,0xF2,0xE2,0x01,0x18,0x08,0x76,0x65,0x72,0x5F,0x72,0x65,0x73,0x70,0x18,0x31,0x48,0x54,0x55,0x6D,0x4E,0x31,0x65,0x70,0x4A,0x38,0x62,0x71,0x44,0x53,0x58,0x74,0x5A,0x5A,0x4B,0x34,0x75,0x74,0x55,0x6B,0x4A,0x64,0x4B,0x57,0x45,0x37,0x6D,0x51,0x75,0x54,0x72,0x74,0x70,0x56,0x68,0x43,0x63,0x64,0x79,0x39,0x38,0x32,0x38,0x31,0x4D,0x0B,0xFE,0x03,0x01,0x88,0x08,0x63,0x61,0x70,0x61,0x63,0x69,0x74,0x79,0x27,0x74,0x68,0x72,0x69,0x66,0x74,0x5F,0x62,0x69,0x6E,0x61,0x72,0x79,0x3B,0x74,0x68,0x72,0x69,0x66,0x74,0x5F,0x63,0x6F,0x6D,0x70,0x61,0x63,0x74,0x3B,0x73,0x6E,0x61,0x70,0x70,0x79,0x5F,0x72,0x61,0x77,0x7F,0x18,0x2B,0x32,0x67,0x66,0x70,0x70,0x33,0x4D,0x41,0x42,0x34,0x37,0x35,0x71,0x34,0x57,0x4E,0x79,0x79,0x75,0x4C,0x36,0x6B,0x50,0x55,0x6A,0x77,0x33,0x6E,0x65,0x64,0x4A,0x4C,0x4B,0x52,0x67,0x69,0x69,0x4A,0x69,0x55,0x6A,0x37,0x5A,0x15,0x82,0x90,0x18,0x15,0x02,0x7F};
    buf.write_to_byte_buf((const char*)b, sizeof(b));

    matrix_coder coder;

    shared_ptr<message> msg = std::make_shared<message>();

    decode_status r = coder.decode_frame(ctx, buf, msg);

    BOOST_TEST(r == DECODE_SUCCESS);
}


BOOST_AUTO_TEST_CASE(test_decode_as_none_forward_msg){

    byte_buf buf;

    // generate buf on demand
    {
        message msg;

        channel_handler_context ctx;

        matrix_coder coder;

        msg.header.msg_name = P2P_GET_PEER_NODES_RESP;
        msg.header.msg_priority = 0;

        auto resp_content = std::make_shared<get_peer_nodes_resp>();
        resp_content->header.__set_magic(TEST_NET);
        resp_content->header.__set_msg_name(P2P_GET_PEER_NODES_RESP);
        resp_content->header.__set_nonce("12345");

        {
            std::map<std::string, std::string> exten_info;
            exten_info["origin_id"] = "bob";
            exten_info["dest_id"] = "alice";
            exten_info["drt"] = "b";
            resp_content->header.__set_exten_info(exten_info);
        }

        matrix::service_core::peer_node_info info;
        info.peer_node_id = "node1";
        info.live_time_stamp = 1;
        info.addr.ip = "192.168.0.2";
        info.addr.port = 10001;
        info.service_list.push_back(std::string("ai_training"));

        std::vector<peer_node_info>  peer_nodes_list;
        peer_nodes_list.push_back(info);
        resp_content->body.__set_peer_nodes_list(peer_nodes_list);

        msg.set_content(resp_content);

        auto r = coder.encode(ctx, msg, buf);

//        std::cout<<"compress: "<< buf.to_string()<<std::endl;
    }


    {
        channel_handler_context ctx;
        variable_value v1;
        v1.value() = std::string("mike");
        ctx.add("LOCAL_NODE_ID", v1);

        matrix_coder coder;

        shared_ptr<message> msg = std::make_shared<message>();

        decode_status r = coder.decode_frame(ctx, buf, msg);

//    std::cout<<"msg name: " << msg->content->header.msg_name <<std::endl;
        std::cout << "msg name: " << msg->content->header << std::endl;


        BOOST_TEST(r == DECODE_SUCCESS);
    }

//    auto r2 = coder.encode(ctx, *msg, buf);
//    std::cout<<"buf: "<< buf.to_string()<<std::endl;
//    BOOST_TEST(r2==ENCODE_SUCCESS);
}

BOOST_AUTO_TEST_CASE(test_decode_as_forward_msg){

    byte_buf buf;

    // generate buf on demand
    {
        message msg;

        channel_handler_context ctx;

        matrix_coder coder;

        msg.header.msg_name = LIST_TRAINING_REQ;
        msg.header.msg_priority = 0;

        auto content = std::make_shared<list_training_req>();
        content->header.__set_magic(TEST_NET);
        content->header.__set_msg_name(LIST_TRAINING_REQ);
        content->header.__set_nonce("12345");

        {
            std::map<std::string, std::string> exten_info;
            exten_info["origin_id"] = "bob";
            exten_info["dest_id"] = "alice";
            exten_info["drt"] = "b";
            content->header.__set_exten_info(exten_info);
        }

        content->body.task_list.push_back("task_1");

        msg.set_content(content);

        auto r = coder.encode(ctx, msg, buf);

    }


    shared_ptr<message> msg = std::make_shared<message>();

    {
        channel_handler_context ctx;
        variable_value v1;
        v1.value() = std::string("mike");
        ctx.add("LOCAL_NODE_ID", v1);

        matrix_coder coder;



        decode_status r = coder.decode_frame(ctx, buf, msg);

//    std::cout<<"msg name: " << msg->content->header.msg_name <<std::endl;
        std::cout << "msg name: " << msg->content->header << std::endl;


        BOOST_TEST(r == DECODE_SUCCESS);
    }

    // encode binary forward message
    {
        channel_handler_context ctx;
        matrix_coder coder;

        auto r2 = coder.encode(ctx, *msg, buf);
        std::cout << "buf: " << buf.to_string() << std::endl;
        BOOST_TEST(r2 == ENCODE_SUCCESS);
    }
}