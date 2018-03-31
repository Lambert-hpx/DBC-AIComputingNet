/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MATRIX_TYPES_H
#define MATRIX_TYPES_H

#include <iosfwd>

#include "protocol.h"
#include "service_message.h"
#include "TToString.h"


using namespace matrix::core;



namespace matrix { namespace service_core {

class msg_header;

class empty;

class network_address;

class task_status;

class peer_node_info;

class ver_req_body;

class ver_req;

class ver_resp_body;

class ver_resp;

class shake_hand_req;

class shake_hand_resp;

class get_peer_nodes_req;

class get_peer_nodes_resp_body;

class get_peer_nodes_resp;

class peer_nodes_broadcast_req_body;

class peer_nodes_broadcast_req;

class start_training_req_body;

class start_training_req;

class stop_training_req_body;

class stop_training_req;

class list_training_req_body;

class list_training_req;

class list_training_resp_body;

class list_training_resp;

typedef struct _msg_header__isset {
  _msg_header__isset() : magic(false), msg_name(false), check_sum(false), session_id(false), exten_info(false) {}
  bool magic :1;
  bool msg_name :1;
  bool check_sum :1;
  bool session_id :1;
  bool exten_info :1;
} _msg_header__isset;

class msg_header : public virtual base {
 public:

  msg_header(const msg_header&);
  msg_header& operator=(const msg_header&);
  msg_header() : magic(0), msg_name(), check_sum(0), session_id(0) {
  }

  virtual ~msg_header() throw();
  int32_t magic;
  std::string msg_name;
  int32_t check_sum;
  int32_t session_id;
  std::map<std::string, std::string>  exten_info;

  _msg_header__isset __isset;

  void __set_magic(const int32_t val);

  void __set_msg_name(const std::string& val);

  void __set_check_sum(const int32_t val);

  void __set_session_id(const int32_t val);

  void __set_exten_info(const std::map<std::string, std::string> & val);

  bool operator == (const msg_header & rhs) const
  {
    if (!(magic == rhs.magic))
      return false;
    if (!(msg_name == rhs.msg_name))
      return false;
    if (!(check_sum == rhs.check_sum))
      return false;
    if (!(session_id == rhs.session_id))
      return false;
    if (__isset.exten_info != rhs.__isset.exten_info)
      return false;
    else if (__isset.exten_info && !(exten_info == rhs.exten_info))
      return false;
    return true;
  }
  bool operator != (const msg_header &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const msg_header & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(msg_header &a, msg_header &b);

std::ostream& operator<<(std::ostream& out, const msg_header& obj);


class empty : public virtual base {
 public:

  empty(const empty&);
  empty& operator=(const empty&);
  empty() {
  }

  virtual ~empty() throw();

  bool operator == (const empty & /* rhs */) const
  {
    return true;
  }
  bool operator != (const empty &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const empty & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(empty &a, empty &b);

std::ostream& operator<<(std::ostream& out, const empty& obj);

typedef struct _network_address__isset {
  _network_address__isset() : ip(false), port(false) {}
  bool ip :1;
  bool port :1;
} _network_address__isset;

class network_address : public virtual base {
 public:

  network_address(const network_address&);
  network_address& operator=(const network_address&);
  network_address() : ip(), port(0) {
  }

  virtual ~network_address() throw();
  std::string ip;
  int16_t port;

  _network_address__isset __isset;

  void __set_ip(const std::string& val);

  void __set_port(const int16_t val);

  bool operator == (const network_address & rhs) const
  {
    if (!(ip == rhs.ip))
      return false;
    if (!(port == rhs.port))
      return false;
    return true;
  }
  bool operator != (const network_address &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const network_address & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(network_address &a, network_address &b);

std::ostream& operator<<(std::ostream& out, const network_address& obj);

typedef struct _task_status__isset {
  _task_status__isset() : task_id(false), status(false) {}
  bool task_id :1;
  bool status :1;
} _task_status__isset;

class task_status : public virtual base {
 public:

  task_status(const task_status&);
  task_status& operator=(const task_status&);
  task_status() : task_id(), status(0) {
  }

  virtual ~task_status() throw();
  std::string task_id;
  int8_t status;

  _task_status__isset __isset;

  void __set_task_id(const std::string& val);

  void __set_status(const int8_t val);

  bool operator == (const task_status & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    if (!(status == rhs.status))
      return false;
    return true;
  }
  bool operator != (const task_status &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const task_status & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(task_status &a, task_status &b);

std::ostream& operator<<(std::ostream& out, const task_status& obj);

typedef struct _peer_node_info__isset {
  _peer_node_info__isset() : peer_node_id(false), live_time_stamp(false), addr(false), service_list(false) {}
  bool peer_node_id :1;
  bool live_time_stamp :1;
  bool addr :1;
  bool service_list :1;
} _peer_node_info__isset;

class peer_node_info : public virtual base {
 public:

  peer_node_info(const peer_node_info&);
  peer_node_info& operator=(const peer_node_info&);
  peer_node_info() : peer_node_id(), live_time_stamp(0) {
  }

  virtual ~peer_node_info() throw();
  std::string peer_node_id;
  int32_t live_time_stamp;
  network_address addr;
  std::vector<std::string>  service_list;

  _peer_node_info__isset __isset;

  void __set_peer_node_id(const std::string& val);

  void __set_live_time_stamp(const int32_t val);

  void __set_addr(const network_address& val);

  void __set_service_list(const std::vector<std::string> & val);

  bool operator == (const peer_node_info & rhs) const
  {
    if (!(peer_node_id == rhs.peer_node_id))
      return false;
    if (!(live_time_stamp == rhs.live_time_stamp))
      return false;
    if (!(addr == rhs.addr))
      return false;
    if (!(service_list == rhs.service_list))
      return false;
    return true;
  }
  bool operator != (const peer_node_info &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const peer_node_info & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(peer_node_info &a, peer_node_info &b);

std::ostream& operator<<(std::ostream& out, const peer_node_info& obj);

typedef struct _ver_req_body__isset {
  _ver_req_body__isset() : version(false), time_stamp(false), addr_me(false), addr_you(false), nonce(false), start_height(false) {}
  bool version :1;
  bool time_stamp :1;
  bool addr_me :1;
  bool addr_you :1;
  bool nonce :1;
  bool start_height :1;
} _ver_req_body__isset;

class ver_req_body : public virtual base {
 public:

  ver_req_body(const ver_req_body&);
  ver_req_body& operator=(const ver_req_body&);
  ver_req_body() : version(0), time_stamp(0), nonce(0), start_height(0) {
  }

  virtual ~ver_req_body() throw();
  int32_t version;
  int64_t time_stamp;
  network_address addr_me;
  network_address addr_you;
  int64_t nonce;
  int32_t start_height;

  _ver_req_body__isset __isset;

  void __set_version(const int32_t val);

  void __set_time_stamp(const int64_t val);

  void __set_addr_me(const network_address& val);

  void __set_addr_you(const network_address& val);

  void __set_nonce(const int64_t val);

  void __set_start_height(const int32_t val);

  bool operator == (const ver_req_body & rhs) const
  {
    if (!(version == rhs.version))
      return false;
    if (!(time_stamp == rhs.time_stamp))
      return false;
    if (!(addr_me == rhs.addr_me))
      return false;
    if (!(addr_you == rhs.addr_you))
      return false;
    if (!(nonce == rhs.nonce))
      return false;
    if (!(start_height == rhs.start_height))
      return false;
    return true;
  }
  bool operator != (const ver_req_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ver_req_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ver_req_body &a, ver_req_body &b);

std::ostream& operator<<(std::ostream& out, const ver_req_body& obj);

typedef struct _ver_req__isset {
  _ver_req__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _ver_req__isset;

class ver_req : public virtual base {
 public:

  ver_req(const ver_req&);
  ver_req& operator=(const ver_req&);
  ver_req() {
  }

  virtual ~ver_req() throw();
  msg_header header;
  ver_req_body body;

  _ver_req__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const ver_req_body& val);

  bool operator == (const ver_req & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const ver_req &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ver_req & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ver_req &a, ver_req &b);

std::ostream& operator<<(std::ostream& out, const ver_req& obj);

typedef struct _ver_resp_body__isset {
  _ver_resp_body__isset() : version(false) {}
  bool version :1;
} _ver_resp_body__isset;

class ver_resp_body : public virtual base {
 public:

  ver_resp_body(const ver_resp_body&);
  ver_resp_body& operator=(const ver_resp_body&);
  ver_resp_body() : version(0) {
  }

  virtual ~ver_resp_body() throw();
  int32_t version;

  _ver_resp_body__isset __isset;

  void __set_version(const int32_t val);

  bool operator == (const ver_resp_body & rhs) const
  {
    if (!(version == rhs.version))
      return false;
    return true;
  }
  bool operator != (const ver_resp_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ver_resp_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ver_resp_body &a, ver_resp_body &b);

std::ostream& operator<<(std::ostream& out, const ver_resp_body& obj);

typedef struct _ver_resp__isset {
  _ver_resp__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _ver_resp__isset;

class ver_resp : public virtual base {
 public:

  ver_resp(const ver_resp&);
  ver_resp& operator=(const ver_resp&);
  ver_resp() {
  }

  virtual ~ver_resp() throw();
  msg_header header;
  ver_resp_body body;

  _ver_resp__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const ver_resp_body& val);

  bool operator == (const ver_resp & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const ver_resp &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ver_resp & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ver_resp &a, ver_resp &b);

std::ostream& operator<<(std::ostream& out, const ver_resp& obj);

typedef struct _shake_hand_req__isset {
  _shake_hand_req__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _shake_hand_req__isset;

class shake_hand_req : public virtual base {
 public:

  shake_hand_req(const shake_hand_req&);
  shake_hand_req& operator=(const shake_hand_req&);
  shake_hand_req() {
  }

  virtual ~shake_hand_req() throw();
  msg_header header;
  empty body;

  _shake_hand_req__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const empty& val);

  bool operator == (const shake_hand_req & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const shake_hand_req &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const shake_hand_req & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(shake_hand_req &a, shake_hand_req &b);

std::ostream& operator<<(std::ostream& out, const shake_hand_req& obj);

typedef struct _shake_hand_resp__isset {
  _shake_hand_resp__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _shake_hand_resp__isset;

class shake_hand_resp : public virtual base {
 public:

  shake_hand_resp(const shake_hand_resp&);
  shake_hand_resp& operator=(const shake_hand_resp&);
  shake_hand_resp() {
  }

  virtual ~shake_hand_resp() throw();
  msg_header header;
  empty body;

  _shake_hand_resp__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const empty& val);

  bool operator == (const shake_hand_resp & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const shake_hand_resp &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const shake_hand_resp & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(shake_hand_resp &a, shake_hand_resp &b);

std::ostream& operator<<(std::ostream& out, const shake_hand_resp& obj);

typedef struct _get_peer_nodes_req__isset {
  _get_peer_nodes_req__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _get_peer_nodes_req__isset;

class get_peer_nodes_req : public virtual base {
 public:

  get_peer_nodes_req(const get_peer_nodes_req&);
  get_peer_nodes_req& operator=(const get_peer_nodes_req&);
  get_peer_nodes_req() {
  }

  virtual ~get_peer_nodes_req() throw();
  msg_header header;
  empty body;

  _get_peer_nodes_req__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const empty& val);

  bool operator == (const get_peer_nodes_req & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const get_peer_nodes_req &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const get_peer_nodes_req & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(get_peer_nodes_req &a, get_peer_nodes_req &b);

std::ostream& operator<<(std::ostream& out, const get_peer_nodes_req& obj);

typedef struct _get_peer_nodes_resp_body__isset {
  _get_peer_nodes_resp_body__isset() : peer_nodes_list(false) {}
  bool peer_nodes_list :1;
} _get_peer_nodes_resp_body__isset;

class get_peer_nodes_resp_body : public virtual base {
 public:

  get_peer_nodes_resp_body(const get_peer_nodes_resp_body&);
  get_peer_nodes_resp_body& operator=(const get_peer_nodes_resp_body&);
  get_peer_nodes_resp_body() {
  }

  virtual ~get_peer_nodes_resp_body() throw();
  std::vector<peer_node_info>  peer_nodes_list;

  _get_peer_nodes_resp_body__isset __isset;

  void __set_peer_nodes_list(const std::vector<peer_node_info> & val);

  bool operator == (const get_peer_nodes_resp_body & rhs) const
  {
    if (!(peer_nodes_list == rhs.peer_nodes_list))
      return false;
    return true;
  }
  bool operator != (const get_peer_nodes_resp_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const get_peer_nodes_resp_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(get_peer_nodes_resp_body &a, get_peer_nodes_resp_body &b);

std::ostream& operator<<(std::ostream& out, const get_peer_nodes_resp_body& obj);

typedef struct _get_peer_nodes_resp__isset {
  _get_peer_nodes_resp__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _get_peer_nodes_resp__isset;

class get_peer_nodes_resp : public virtual base {
 public:

  get_peer_nodes_resp(const get_peer_nodes_resp&);
  get_peer_nodes_resp& operator=(const get_peer_nodes_resp&);
  get_peer_nodes_resp() {
  }

  virtual ~get_peer_nodes_resp() throw();
  msg_header header;
  get_peer_nodes_resp_body body;

  _get_peer_nodes_resp__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const get_peer_nodes_resp_body& val);

  bool operator == (const get_peer_nodes_resp & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const get_peer_nodes_resp &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const get_peer_nodes_resp & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(get_peer_nodes_resp &a, get_peer_nodes_resp &b);

std::ostream& operator<<(std::ostream& out, const get_peer_nodes_resp& obj);

typedef struct _peer_nodes_broadcast_req_body__isset {
  _peer_nodes_broadcast_req_body__isset() : peer_nodes_list(false) {}
  bool peer_nodes_list :1;
} _peer_nodes_broadcast_req_body__isset;

class peer_nodes_broadcast_req_body : public virtual base {
 public:

  peer_nodes_broadcast_req_body(const peer_nodes_broadcast_req_body&);
  peer_nodes_broadcast_req_body& operator=(const peer_nodes_broadcast_req_body&);
  peer_nodes_broadcast_req_body() {
  }

  virtual ~peer_nodes_broadcast_req_body() throw();
  std::vector<peer_node_info>  peer_nodes_list;

  _peer_nodes_broadcast_req_body__isset __isset;

  void __set_peer_nodes_list(const std::vector<peer_node_info> & val);

  bool operator == (const peer_nodes_broadcast_req_body & rhs) const
  {
    if (!(peer_nodes_list == rhs.peer_nodes_list))
      return false;
    return true;
  }
  bool operator != (const peer_nodes_broadcast_req_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const peer_nodes_broadcast_req_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(peer_nodes_broadcast_req_body &a, peer_nodes_broadcast_req_body &b);

std::ostream& operator<<(std::ostream& out, const peer_nodes_broadcast_req_body& obj);

typedef struct _peer_nodes_broadcast_req__isset {
  _peer_nodes_broadcast_req__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _peer_nodes_broadcast_req__isset;

class peer_nodes_broadcast_req : public virtual base {
 public:

  peer_nodes_broadcast_req(const peer_nodes_broadcast_req&);
  peer_nodes_broadcast_req& operator=(const peer_nodes_broadcast_req&);
  peer_nodes_broadcast_req() {
  }

  virtual ~peer_nodes_broadcast_req() throw();
  msg_header header;
  peer_nodes_broadcast_req_body body;

  _peer_nodes_broadcast_req__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const peer_nodes_broadcast_req_body& val);

  bool operator == (const peer_nodes_broadcast_req & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const peer_nodes_broadcast_req &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const peer_nodes_broadcast_req & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(peer_nodes_broadcast_req &a, peer_nodes_broadcast_req &b);

std::ostream& operator<<(std::ostream& out, const peer_nodes_broadcast_req& obj);

typedef struct _start_training_req_body__isset {
  _start_training_req_body__isset() : task_id(false), select_mode(false), master(false), peer_nodes_list(false), server_specification(false), server_count(false), training_engine(false), code_dir(false), entry_file(false), data_dir(false), checkpoint_dir(false), hyper_parameters(false) {}
  bool task_id :1;
  bool select_mode :1;
  bool master :1;
  bool peer_nodes_list :1;
  bool server_specification :1;
  bool server_count :1;
  bool training_engine :1;
  bool code_dir :1;
  bool entry_file :1;
  bool data_dir :1;
  bool checkpoint_dir :1;
  bool hyper_parameters :1;
} _start_training_req_body__isset;

class start_training_req_body : public virtual base {
 public:

  start_training_req_body(const start_training_req_body&);
  start_training_req_body& operator=(const start_training_req_body&);
  start_training_req_body() : task_id(), select_mode(0), master(), server_specification(), server_count(0), training_engine(0), code_dir(), entry_file(), data_dir(), checkpoint_dir(), hyper_parameters() {
  }

  virtual ~start_training_req_body() throw();
  std::string task_id;
  int8_t select_mode;
  std::string master;
  std::vector<std::string>  peer_nodes_list;
  std::string server_specification;
  int32_t server_count;
  int32_t training_engine;
  std::string code_dir;
  std::string entry_file;
  std::string data_dir;
  std::string checkpoint_dir;
  std::string hyper_parameters;

  _start_training_req_body__isset __isset;

  void __set_task_id(const std::string& val);

  void __set_select_mode(const int8_t val);

  void __set_master(const std::string& val);

  void __set_peer_nodes_list(const std::vector<std::string> & val);

  void __set_server_specification(const std::string& val);

  void __set_server_count(const int32_t val);

  void __set_training_engine(const int32_t val);

  void __set_code_dir(const std::string& val);

  void __set_entry_file(const std::string& val);

  void __set_data_dir(const std::string& val);

  void __set_checkpoint_dir(const std::string& val);

  void __set_hyper_parameters(const std::string& val);

  bool operator == (const start_training_req_body & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    if (!(select_mode == rhs.select_mode))
      return false;
    if (!(master == rhs.master))
      return false;
    if (!(peer_nodes_list == rhs.peer_nodes_list))
      return false;
    if (!(server_specification == rhs.server_specification))
      return false;
    if (!(server_count == rhs.server_count))
      return false;
    if (!(training_engine == rhs.training_engine))
      return false;
    if (!(code_dir == rhs.code_dir))
      return false;
    if (!(entry_file == rhs.entry_file))
      return false;
    if (!(data_dir == rhs.data_dir))
      return false;
    if (!(checkpoint_dir == rhs.checkpoint_dir))
      return false;
    if (!(hyper_parameters == rhs.hyper_parameters))
      return false;
    return true;
  }
  bool operator != (const start_training_req_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const start_training_req_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(start_training_req_body &a, start_training_req_body &b);

std::ostream& operator<<(std::ostream& out, const start_training_req_body& obj);

typedef struct _start_training_req__isset {
  _start_training_req__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _start_training_req__isset;

class start_training_req : public virtual base {
 public:

  start_training_req(const start_training_req&);
  start_training_req& operator=(const start_training_req&);
  start_training_req() {
  }

  virtual ~start_training_req() throw();
  msg_header header;
  start_training_req_body body;

  _start_training_req__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const start_training_req_body& val);

  bool operator == (const start_training_req & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const start_training_req &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const start_training_req & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(start_training_req &a, start_training_req &b);

std::ostream& operator<<(std::ostream& out, const start_training_req& obj);

typedef struct _stop_training_req_body__isset {
  _stop_training_req_body__isset() : task_id(false) {}
  bool task_id :1;
} _stop_training_req_body__isset;

class stop_training_req_body : public virtual base {
 public:

  stop_training_req_body(const stop_training_req_body&);
  stop_training_req_body& operator=(const stop_training_req_body&);
  stop_training_req_body() : task_id() {
  }

  virtual ~stop_training_req_body() throw();
  std::string task_id;

  _stop_training_req_body__isset __isset;

  void __set_task_id(const std::string& val);

  bool operator == (const stop_training_req_body & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    return true;
  }
  bool operator != (const stop_training_req_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const stop_training_req_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(stop_training_req_body &a, stop_training_req_body &b);

std::ostream& operator<<(std::ostream& out, const stop_training_req_body& obj);

typedef struct _stop_training_req__isset {
  _stop_training_req__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _stop_training_req__isset;

class stop_training_req : public virtual base {
 public:

  stop_training_req(const stop_training_req&);
  stop_training_req& operator=(const stop_training_req&);
  stop_training_req() {
  }

  virtual ~stop_training_req() throw();
  msg_header header;
  stop_training_req_body body;

  _stop_training_req__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const stop_training_req_body& val);

  bool operator == (const stop_training_req & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const stop_training_req &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const stop_training_req & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(stop_training_req &a, stop_training_req &b);

std::ostream& operator<<(std::ostream& out, const stop_training_req& obj);

typedef struct _list_training_req_body__isset {
  _list_training_req_body__isset() : task_list(false) {}
  bool task_list :1;
} _list_training_req_body__isset;

class list_training_req_body : public virtual base {
 public:

  list_training_req_body(const list_training_req_body&);
  list_training_req_body& operator=(const list_training_req_body&);
  list_training_req_body() {
  }

  virtual ~list_training_req_body() throw();
  std::vector<std::string>  task_list;

  _list_training_req_body__isset __isset;

  void __set_task_list(const std::vector<std::string> & val);

  bool operator == (const list_training_req_body & rhs) const
  {
    if (!(task_list == rhs.task_list))
      return false;
    return true;
  }
  bool operator != (const list_training_req_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const list_training_req_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(list_training_req_body &a, list_training_req_body &b);

std::ostream& operator<<(std::ostream& out, const list_training_req_body& obj);

typedef struct _list_training_req__isset {
  _list_training_req__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _list_training_req__isset;

class list_training_req : public virtual base {
 public:

  list_training_req(const list_training_req&);
  list_training_req& operator=(const list_training_req&);
  list_training_req() {
  }

  virtual ~list_training_req() throw();
  msg_header header;
  list_training_req_body body;

  _list_training_req__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const list_training_req_body& val);

  bool operator == (const list_training_req & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const list_training_req &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const list_training_req & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(list_training_req &a, list_training_req &b);

std::ostream& operator<<(std::ostream& out, const list_training_req& obj);

typedef struct _list_training_resp_body__isset {
  _list_training_resp_body__isset() : task_status_list(false) {}
  bool task_status_list :1;
} _list_training_resp_body__isset;

class list_training_resp_body : public virtual base {
 public:

  list_training_resp_body(const list_training_resp_body&);
  list_training_resp_body& operator=(const list_training_resp_body&);
  list_training_resp_body() {
  }

  virtual ~list_training_resp_body() throw();
  std::vector<task_status>  task_status_list;

  _list_training_resp_body__isset __isset;

  void __set_task_status_list(const std::vector<task_status> & val);

  bool operator == (const list_training_resp_body & rhs) const
  {
    if (!(task_status_list == rhs.task_status_list))
      return false;
    return true;
  }
  bool operator != (const list_training_resp_body &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const list_training_resp_body & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(list_training_resp_body &a, list_training_resp_body &b);

std::ostream& operator<<(std::ostream& out, const list_training_resp_body& obj);

typedef struct _list_training_resp__isset {
  _list_training_resp__isset() : header(false), body(false) {}
  bool header :1;
  bool body :1;
} _list_training_resp__isset;

class list_training_resp : public virtual base {
 public:

  list_training_resp(const list_training_resp&);
  list_training_resp& operator=(const list_training_resp&);
  list_training_resp() {
  }

  virtual ~list_training_resp() throw();
  msg_header header;
  list_training_resp_body body;

  _list_training_resp__isset __isset;

  void __set_header(const msg_header& val);

  void __set_body(const list_training_resp_body& val);

  bool operator == (const list_training_resp & rhs) const
  {
    if (!(header == rhs.header))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const list_training_resp &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const list_training_resp & ) const;

  uint32_t read(protocol* iprot);
  uint32_t write(protocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(list_training_resp &a, list_training_resp &b);

std::ostream& operator<<(std::ostream& out, const list_training_resp& obj);

}} // namespace

#endif
