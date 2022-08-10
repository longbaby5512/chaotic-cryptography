# Cryptography base on chaos theory

## Application

In this modude, the project was used [Clion](https://www.jetbrains.com/clion) to code.

## How to run this module

- Step 1: Clone module using command line
```Bash
git clone https://github.com/longbaby5512/chaotic-cryptography.git
```

- Step 2: Set up type of build. Default <b>Debug Build</b> is installed. But if you want to run fast, you must add <b>Release Build</b> by click add icon above Debug Build name.

## How to config module

- Create new cypher by default which is permutation block, substitution block and diffusion block all using Logistic Map. In this module, it also have Sin Map:

```C++
auto cypher = ChaoticCypher();
```

- Init crypto mode and key for encrypt/decrypt:
```C++
cypher.init(ChaoticMap.ENCRYPT_MODE, key); // Encryipton
cypher.init(ChaoticMap.DECRYPT_MODE, key); // Decryption
```

- Encryption/Decryption:
```C++
dataAfter=cypher.doFinal(data);
```

## Stay in touch
- Facebook: [Long Nguyen Van](https://www.facebook.com/longkenvy)
- Github: [Nguyễn Văn Long](https://github.com/longbaby5512)
- Email: [long.nv120900@gmail.com](mailto:long.nv120900@gmail.com)
- Linkedin: [Nguyễn Văn Long](https://www.linkedin.com/in/nguyenvanlong)
- Phone: [+84 972 976 843](tel:+84972976843)
