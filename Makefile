.PHONY: all fclean clean re run

all:
	make -C BSD_UDP_CLIENT/
	make -C BSD_UDP_SERVER/

clean:
	make -C BSD_UDP_CLIENT/ clean
	make -C BSD_UDP_SERVER/ clean

fclean:
	make -C BSD_UDP_CLIENT/ fclean
	make -C BSD_UDP_SERVER/ fclean

re: fclean all

run: all
	./udp_server & ./udp_client