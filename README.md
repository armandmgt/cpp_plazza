# Plazza

The goal of the project is to find prototyped data (email, phone number, ip address).

## Make the project

```bash
make fclean && make
```
## Run the project

```bash
./plazza [number of threads]
```

Number of threads : This is the maximum number of threads for each process created 
by the father process 

## Command 

To parse your files you need to prototype your command as follows : 

```sh
[filename ...] [DATA_TYPE] ; [filename ...] [DATA_TYPE] ...
```

### DATA_TYPE :

* PHONE_NUMBER
* EMAIL_ADDRESS
* IP_ADDRESS

---

## Author

* **Sandra Lundh** - *Jar Jar Binks*
* **Armand Megrot** - *Yoda*
* **Thomas Burgaud** - *Darth Vader*
