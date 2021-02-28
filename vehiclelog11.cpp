#include <vehiclelog11.hpp>

using namespace eosio;

ACTION vehiclelog11::grantuser(name user) {
  require_auth(_self);
  
  whitelist existing_whitelist(_code, _code.value);
  auto itr = existing_whitelist.find( user.value );
  eosio::check(itr == existing_whitelist.end(), "User already exists");

  existing_whitelist.emplace(_self, [&]( auto& w ) {
     w.user = user;
  });
}

ACTION vehiclelog11::revokeuser(name user) {
  require_auth(_self);
  whitelist existing_whitelist(user, user.value);
  auto itr = existing_whitelist.find( user.value );
  eosio::check(itr != existing_whitelist.end(), "User does not exist");
  
  existing_whitelist.erase(itr);

}

ACTION vehiclelog11::newsensor( name owner, uint64_t id, std::string location, const std::vector<std::string> labels) {

   require_auth(owner);
   eosio::check(labels.size() < 10, "Too many labels");

   whitelist existing_whitelist(owner, owner.value);
   auto itr1 = existing_whitelist.find( owner.value );
   eosio::check(itr1 != existing_whitelist.end(), "User not allowed");
   
   sensors existing_sensors(owner, owner.value);
   auto itr2 = existing_sensors.find( id );
   eosio::check(itr2 == existing_sensors.end(), "Sensor already exists");

   existing_sensors.emplace(owner, [&]( auto& s ) {
      s.owner = owner;
      s.id = id;
      s.location = location;
      s.labels = labels;
   });

}

ACTION vehiclelog11::deletesensor( name owner, uint64_t id) {
   require_auth(owner);

   sensors existing_sensors(owner, owner.value);
   auto itr = existing_sensors.find( id );
   eosio::check(itr != existing_sensors.end(), "Sensor does not exist");

   existing_sensors.erase(itr);

}

ACTION vehiclelog11::multiupload( name owner,  uint64_t id,  uint64_t timestamp, std::vector<double> values) {
   require_auth(owner);

   eosio::check(values.size() < 10, "Too many sensor values");

   whitelist existing_whitelist(owner, owner.value);
   auto itr1 = existing_whitelist.find( owner.value );
   eosio::check(itr1 != existing_whitelist.end(), "User not allowed");
    sensors existing_sensors(owner, owner.value);
    auto itr2 = existing_sensors.find( id );
    eosio::check(itr2 != existing_sensors.end(), "Sensor does not exist");

    eosio::check(itr2->labels.size() == values.size(), "Values/Labels array size mismatch");

}
