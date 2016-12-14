namespace py simpledb

typedef byte version_t
typedef i64 time_t_def

struct File {
  // meta dados
  1: time_t_def creation,
  2: time_t_def modification,
  3: version_t version,

  // conteudo do arquivo
  4: string name,
  5: string content
}


service SimpleDB
{
  File get(1: string url),
  list<File> get_list(1: string url)
  version_t add(1: string url, 2: string content),
  version_t update(1: string url, 2: string content),
  File delete_file(1: string url),
  version_t update_with_version(1: string url, 2: string content, 3: version_t version),
  File delete_with_version(1: string url, 2: version_t version)


  // referente a comunicacao entre servidores
  void update_server()
  File get_v(1: string url_v, 2: string url),

  // two-way handshake
  version_t add_tw(1: string url, 2: string content),
  File delete_file_tw(1: string url),
  bool get_response(1: string msg),
  void tw_feedback(1: string msg)
}
