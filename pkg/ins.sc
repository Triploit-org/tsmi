func install
{
  g++ main.cpp -o tsmi -w -static -std=c++11
  chmod +x tsmi
  sudo mv tsmi /usr/bin/tsmi
}

func update
{
  &install
}

func remove
{
  sudo rm /usr/bin/tsmi
}

func werror
{
  @echo There is no Windows-Support yet.
  @echo Install this package manually.
}

func install_win
{
  &werror
}

func remove_win
{
  &werror
}

func update_win
{
  &werror
}
