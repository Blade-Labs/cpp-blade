# Setting Up

Setting up cpp-blade requires a few steps. Here's a brief overview of the process:

Clone the cpp-blade repository:

```bash
git clone https://github.com/Blade-Labs/cpp-blade.git
```

Install the required dependencies:

```sql
sudo apt-get update
sudo apt-get install -y cmake g++ make libgmp-dev libssl-dev
```

Build the cpp-blade binary:

```bash
cd cpp-blade
cmake .
make
```

Run the cpp-blade node:

```bash
./cpp-blade-node
```

The above steps are the basic ones required to set up cpp-blade. However, there are other configuration options that you may want to explore depending on your use case. You can find more information in the cpp-blade documentation. Additionally, it's worth noting that running a Blade node can be resource-intensive, so you may need to ensure that your system meets the hardware requirements before running cpp-blade.
