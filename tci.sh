tci_base="/etc/config"

tci_set_r() {
    echo "$3" > "$1/$2"
}

tci_value_r() {
    cat "$1/$2" || echo "$3"
}

tci_set() {
    tci_set_r "$tci_base" "$1" "$2"
}

tci_value() {
    tci_value_r "$tci_base" "$1" "$2"
}
