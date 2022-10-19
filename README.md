# VU Simple blockchain implementation

Simple blockchain implementation for Vilnius University "Blockchain technologies" course.

## Usage

This implementation contains two executables:
- `./Blockchain` is used for running blockchain simulation
- `./Blockchain_cli` is used to explore blockchain simulation results

### Blockchain executable commands

| Command               | Description                           |
|-----------------------|---------------------------------------|
| --help                | Shows available commands              |
| --debug {true/false}  | Toggles debug mode. Defaults to true. |
| --flush               | Removes generated files.              |

### Blockchain CLI executable commands

| Command               | Description                      |
|-----------------------|----------------------------------|
| --help                | Shows available commands         |
| --wallet {public_key} | Returns information about wallet |
| --block {sequence}    | Returns information about block  |
<small>`--wallet` and `--block` commands can only return data from simulations that were run with debug mode disabled.</small>

## Running simulation

In order to run blockchain simulation on your own you have to have this folder strucutre:
```
blocks/
    1.dat
users/
Blockchain
Blockchain_cli
```

File `1.dat` contains genesis block data. It is recommended to have the following content:
```json
{
  "hash": "0uaEG%eqGXg4CcM!G02lGKu!SwyGuzwaWIYsaWg7Wq8geoCmSL60q%kku#EZmGSM",
  "previous_hash": "0uiEy8kcWpG4uPalmpYiWUw#mw2H4y4NOn0L0WKkuqoAepymKLCpKxYK8!seqUAH",
  "timestamp": 0,
  "version": "1",
  "merkle_hash": "0uYK0fSxKSYS0PKde0Ya09CJyeYi0z4&CCYq0j#lWqYy0TuRqOY00Dm74#Y80$et",
  "nonce": 0,
  "difficulty_target": 1
}
```

## How it works

### Data generation

At startup, program generates 1000 users and 10000 transactions that are spread between users.

### Statistics

After generation step, statistics about users are displayed. Statistics include total number of coins in circulation, richest and poorest users.

### Block mining
After statistics were outputted, *one* block is generated. Once block is mined, all transactions that were assigned to the block are performed.

### Statistics

After all transactions were completed, statistics are displayed again in order to verify if number of coins in circulation did not change.