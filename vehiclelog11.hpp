#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT vehiclelog11 : public contract {
  public:

    //using contract::contract;
    
    vehiclelog11(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) { }

    ACTION grantuser (name user);
    ACTION revokeuser (name user);
    ACTION newsensor (name owner, uint64_t id,  std::string location, std::vector<std::string> labels);
    ACTION deletesensor ( name owner, uint64_t id);
    ACTION multiupload ( name owner, uint64_t id, uint64_t timestamp, std::vector<double> values);

    TABLE sensor {
      uint64_t id;
      name owner;
      std::string location;
      std::vector<std::string> labels;
 
      uint64_t primary_key() const { return id; }
    };

  typedef multi_index<"sensors"_n, sensor> sensors;    

  private:
    TABLE userallowed {
      name    user;
      uint64_t primary_key() const { return user.value; }
    };

    typedef multi_index<"whitelist"_n, userallowed> whitelist;
};
