# Cpp Blade SDK

## Build

`cmake --preset linux-x64-debug`
`cmake --build --preset linux-x64-debug`

## Create account (direct)

./blade-cpp createAccount <operatorAccountId> <operatorPrivateKey ED25519>

Example: `./blade-cpp createAccount 0.0.8298 f38f262dbbb197a0b3aaff0cf76ea573a1185b5fe8e1cfe13c41efdc280b5073`


## Create account (Blade) (in progress)

./blade-cpp createAccountBlade 

Example: `./blade-cpp createAccountBlade`

## Import

./blade-cpp import "<12-word-menmonic>" 

Example: `./blade-cpp import "bone govern tent wrong arrive miracle hurt bracket tomorrow urge pioneer gate"`

## Sign

./blade-cpp sign "<message>" <privateKey ECDSA>

Example: `./blade-cpp sign "test" 4A4935857096E9D97955800946A66F87DE35DA54EC9A91B7F316B20D2B334B3F`

## Verify

./blade-cpp verify "<message>" <signature hex> <public key>

Example: `./blade-cpp verify "test" eee555e99410caa406d73ebf192dd88bee5623e14b77a0932cfdd517c0ff5d895a42508f54e10093ed378728c4f7a6ee2012193451a0a37b3df221ff8eb3d26b 03D01617265176DCAD9EF9993A2B364D372E901530CAD667F25DA1E37F45CFAB77`



Account Id: 0.0.3657386
SeedPhrase: bone govern tent wrong arrive miracle hurt bracket tomorrow urge pioneer gate
PrivateKey: 5AF278182C8646A09ACD8FD9A3131B8A83EFEC31B87B63CFD53E46794081614F
Public key: 021B55E5B276C53AFF49F5330F550CB6A48EE95D19E455E649811F56B4D1B36419