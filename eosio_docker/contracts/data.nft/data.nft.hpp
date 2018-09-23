/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {
   using std::string;
   typedef uint128_t uuid;
   typedef uint64_t id_type;
   typedef string uri_type;

   class nft : public contract {
      public:
         nft(account_name self) : contract(self), tokens(_self, _self) {}

         void create(account_name issuer, string symbol);

         void issue( account_name to,
                     asset quantity,
                     vector<string> uris,
                     string name,
                     string metadata,
                     string memo);

         void approve( account_name authorizer,
                        account_name spender,
                        id_type id);

         void transferfrom(account_name spender,
                           account_name from,
                           account_name to,
                           id_type id,
                           string memo);

         void transfer(account_name from,
                        account_name to,
                        id_type id,
                        string memo);

         void subscribe( account_name authorizer,
                        account_name to,
                        id_type id,
                        string memo );

         void burn(account_name owner,
                     id_type token_id);

         void setrampayer(account_name payer, id_type id);


         // @abi table accounts i64
         struct account {

               asset balance;

               uint64_t primary_key() const { return balance.symbol.name(); }
         };

         // @abi table stat i64
         struct stats {
               asset supply;
               account_name issuer;

               uint64_t primary_key() const { return supply.symbol.name(); }
               account_name get_issuer() const { return issuer; }
         };


         // @abi table token i64
         struct token {
               id_type id;          // Unique 64 bit identifier,
               uri_type uri;        // RFC 3986
               account_name owner;  // token owner
               account_name spender;
               asset value;         // token value (1 SYS)
               string name;	 // token name
               string metadata; // metadata
               vector<string> subscribers;

               id_type primary_key() const { return id; }
               account_name get_owner() const { return owner; }
               uint64_t get_symbol() const { return value.symbol.name(); }
               uint64_t get_name() const { return string_to_name(name.c_str()); }

         };

         using account_index = eosio::multi_index<N(accounts), account>;

         using currency_index =  eosio::multi_index<N(stat), stats,
                                 indexed_by< N( byissuer ), const_mem_fun< stats, account_name, &stats::get_issuer> > >;

         using token_index = eosio::multi_index<N(token), token,
                           indexed_by< N( byowner ), const_mem_fun< token, account_name, &token::get_owner> >,
                           indexed_by< N( bysymbol ), const_mem_fun< token, uint64_t, &token::get_symbol> >,
                           indexed_by< N( byname ), const_mem_fun< token, uint64_t, &token::get_name> > >;

      private:
         friend eosiosystem::system_contract;

         token_index tokens;

         void mint(account_name owner, account_name ram_payer, asset value, string uri, string name, string metadata);

         void sub_balance(account_name owner, asset value);
         void add_balance(account_name owner, asset value, account_name ram_payer);
         void sub_supply(asset quantity);
         void add_supply(asset quantity);
   };
} /// namespace eosio
