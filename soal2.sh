#awk '/wlan0/ {arr[$0]++} END {for (i in arr) {print i} }' dmesg.log

awk '/wlan0/ {arr[$0]++}
	END {
		name=1
		for (i in arr) {
			print i >> "wlan_log/wlan0.log."name
			#print name i
			name++
		}
	}' dmesg.log
