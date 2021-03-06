// Generated by gencpp from file sorohack_tree/BTGoal.msg
// DO NOT EDIT!


#ifndef SOROHACK_TREE_MESSAGE_BTGOAL_H
#define SOROHACK_TREE_MESSAGE_BTGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace sorohack_tree
{
template <class ContainerAllocator>
struct BTGoal_
{
  typedef BTGoal_<ContainerAllocator> Type;

  BTGoal_()
    : bt_action_goal()  {
    }
  BTGoal_(const ContainerAllocator& _alloc)
    : bt_action_goal(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _bt_action_goal_type;
  _bt_action_goal_type bt_action_goal;





  typedef boost::shared_ptr< ::sorohack_tree::BTGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sorohack_tree::BTGoal_<ContainerAllocator> const> ConstPtr;

}; // struct BTGoal_

typedef ::sorohack_tree::BTGoal_<std::allocator<void> > BTGoal;

typedef boost::shared_ptr< ::sorohack_tree::BTGoal > BTGoalPtr;
typedef boost::shared_ptr< ::sorohack_tree::BTGoal const> BTGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sorohack_tree::BTGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::sorohack_tree::BTGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace sorohack_tree

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'sorohack_tree': ['/home/igmitsio/pepper_ws/devel/share/sorohack_tree/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::sorohack_tree::BTGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sorohack_tree::BTGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sorohack_tree::BTGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sorohack_tree::BTGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sorohack_tree::BTGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sorohack_tree::BTGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::sorohack_tree::BTGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "089d672a9a4e6b26982ebad40e0104ea";
  }

  static const char* value(const ::sorohack_tree::BTGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x089d672a9a4e6b26ULL;
  static const uint64_t static_value2 = 0x982ebad40e0104eaULL;
};

template<class ContainerAllocator>
struct DataType< ::sorohack_tree::BTGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sorohack_tree/BTGoal";
  }

  static const char* value(const ::sorohack_tree::BTGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sorohack_tree::BTGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# goal of the action, since this is a general action, a string is ok\n\
string bt_action_goal\n\
";
  }

  static const char* value(const ::sorohack_tree::BTGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sorohack_tree::BTGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.bt_action_goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct BTGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sorohack_tree::BTGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sorohack_tree::BTGoal_<ContainerAllocator>& v)
  {
    s << indent << "bt_action_goal: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.bt_action_goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SOROHACK_TREE_MESSAGE_BTGOAL_H
