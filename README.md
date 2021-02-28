# Smart Contracts

This example is to demonstrate a basic smart contract that can maintain records of different sensors and the data being stored. This is to demonstrate how data can be stored in the blockchain from vehicles directly through IOT devices.


 To add code permission to certain account
cleos -u {node address} set account permission {account name} active --add-code
{node address} - for test net currently we use https://testnet.telos.caleos.io

- To build smart contract (generate wasm and abi files)
eosio-cpp -I include -o {smart contract file name}.wasm src/{smart contract file name}.cpp --abigen

- To deploy smart contract
cleos -u {node address} set contract {contract account name} . --abi {smart contract file name}.abi -p {contract account name}@active
{node address} - for test net currently we use https://testnet.telos.caleos.io


You can interact with the smart contract here on the testnet:

https://telos-test.bloks.io/account/hacklogistic?loadContract=true&tab=Tables&table=sensors&account=hacklogistic&scope=hacklogistic&limit=100&action=grantuser
