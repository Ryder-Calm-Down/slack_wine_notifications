import subprocess
import time
from PIL import Image
from PIL import ImageChops
import requests


def get_screenshot_box_dimensions():
    """Returns the dimensions of the screenshot box"""
    return "1520,35,80,50"


def get_screenshot_path():
    """Returns on file path of the screenshot"""
    return '/tmp/slack_wine_screencapture.jpg'


def take_screenshot():
    """Takes a full screenshot of osx"""
    output_file = get_screenshot_path()
    command = ['screencapture', '-x', '-R{}'.format(get_screenshot_box_dimensions()), output_file]
    subprocess.call(command)


def check_if_slack_notification():
    """Returns boolean whether or not we have a slack notification"""
    current_screen = Image.open(get_screenshot_path())
    notification_screen = Image.open('./new_slack_notification.jpg')
    diff = ImageChops.difference(current_screen, notification_screen)
    if list(current_screen.getdata()) == list(notification_screen.getdata()):
        return True
    return False


def notify_wine_machine():
    """Sends a get request to the wine machine"""
    url = 'http://10.0.0.1/'
    requests.get(url)


def main():
    """Run application"""
    try:
        while True:
            take_screenshot()
            if check_if_slack_notification():
                print('New Slack Notification')
                notify_wine_machine()
                time.sleep(4)
            time.sleep(1)
    except KeyboardInterrupt:
        print('Shutting down')


if __name__ == '__main__':
    main()
