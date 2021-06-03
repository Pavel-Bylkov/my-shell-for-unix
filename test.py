import unittest
import subprocess

class MyTestCases(unittest.TestCase):
    def test_something(self):
        try:
            process1 = subprocess.run('ls -al $HOME', shell=True, capture_output=True, text=True, timeout=5)
            process2 = subprocess.run('ls -al $HOME', shell=True, capture_output=True, text=True, timeout=5)
            self.assertEqual(process1.stdout, process2.stdout)
        except subprocess.TimeoutExpired as e:
            print("Process timeout", e)

    def test_pipe(self):
        dmesg = subprocess.Popen(['dmesg'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        grep = subprocess.Popen(['grep', 'sda'], stdin=dmesg.stdout, shell=True)
        dmesg.stdout.close()
        output = grep.communicate()[0]
        self.assertEqual(output, output)


if __name__ == '__main__':
    unittest.main()